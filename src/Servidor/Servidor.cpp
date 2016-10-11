#include "Servidor.h"

#include <arpa/inet.h>
//#include <asm-generic/socket.h>
//#include <bits/socket_type.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <SDL2/SDL_mutex.h>
#include <unistd.h>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <SDL2/SDL.h>
#include "../Common/Log.h"
#include "../Common/MensajeStruct.h"
#include "./Modelo/EscenarioS.h"
#include "Usuario.h"

using namespace std;


SDL_mutex *mutexQueue;



void* Servidor::procesarMensajesMain (void *data) {
	mensajeStruct msg;
	Servidor* context = (Servidor*)data;
	bool finish = false;
	int result;

	while(!finish && !context->cerrarPrograma){
		if (!context->colaPrincipalMensajes.empty()){
			msg=context->colaPrincipalMensajes.front();
			context->colaPrincipalMensajes.pop();
			//printf("Procesando Mensaje %s",msg.message.c_str());
			Log::log('s',1,"Procesando Mensaje: ",msg.message.c_str());
			result = context->procesarMensajeCola(msg);
			finish = (result != 0);
		}
	}
	return 0;

}

int Servidor::loginInterpretarMensaje(mensajeStruct msg){

	mensajeStruct mensaje;

	mensaje.objectId = "00";

	if (this->contenedor->iniciarSesion(msg.message, msg.socketCli)) {
		std::cout << "OK"  <<endl;
		mensaje.tipo = LOG_OK;
		mensaje.message = this->contenedor->getIdNombresUsuarios(msg.message);
	}else{
		std::cout << "DENEGADO" <<endl;
		mensaje.tipo = LOG_NOTOK;
		mensaje.message = "";
	}

	Mensajeria::encodeAndSend(msg.socketCli, &mensaje);

	return 0;
}

int Servidor::procesarMensajeCola(mensajeStruct msg){
	//EN FUNCIÓN AL TIPO DE MSJ VER QUE SE HACE

	switch (msg.tipo){
		case LOGIN:
			loginInterpretarMensaje(msg);
			break;
		case ENVIAR_CHAT_FIN:
			enviarChat(msg);
			break;
		case RECIBIR_CHATS:
			recibirTodosLosChats(msg);
			break;
		case DISCONNECTED:
			procesarDesconexion(msg);
			break;
		case RECIBIR_HANDSHAKE:
			handshake(msg);
			break;
		case PULSA_TECLA:
			procesarTeclaPulsada(msg);
			break;
	}

	return 0;
}

void Servidor::procesarTeclaPulsada(mensajeStruct msg){

	Usuario* usuario = this->contenedor->getUsuarioBySocket(msg.socketCli);
   list<mensajeStruct> mensajesRta;

   mensajesRta = this->escenario->moverJugador(1,msg.message);


	for(auto const &user :  this->contenedor->socket_usuario) {
	  if(user.second->isConectado()){
		  queue<mensajeStruct>* colaCliente = socketIdQueue[user.first];

			for (mensajeStruct msgRta : mensajesRta) {
				msgRta.socketCli = user.first;
				colaCliente->push(msgRta);
			 }


			msg.tipo=ESCENARIO_UPD;
			msg.objectId="X0";
			stringstream posX;

			posX << this->posicionXHarcodeada;
			msg.message= posX.str();
			colaCliente->push(msg);

			posX.str("");
	  }
	}

	--this->posicionXHarcodeada;
}

void Servidor::handshake(mensajeStruct msg){
	//apunto a la cola de mensajes de clientes que voy a mandar mensajes.
	queue<mensajeStruct>* colaCliente = socketIdQueue[msg.socketCli];

	 /*   Parser *parser = new Parser();
	    parser->parsearArchivoXML(XML_PATH);

	    //MANDO DIMENSIONES DE VENTANA.
	    colaCliente->push(parser->getVentana());
		//MANDAR SPRITES
	    for(std::vector<mensajeStruct>::iterator i = parser->getListaSprites().begin(); i != parser->getListaSprites().end(); ++i) {
	    	   colaCliente->push(*i);
	    }
	    //MANDAR OBJETOS NUEVOS
	    for(std::vector<mensajeStruct>::iterator i = parser->getListaObjetos().begin(); i != parser->getListaObjetos().end(); ++i) {
	    	   colaCliente->push(*i);
	    }
	    //MANDAR FONDO
	    for(std::vector<mensajeStruct>::iterator i = parser->getListaFondos().begin(); i != parser->getListaFondos().end(); ++i) {
	    	   colaCliente->push(*i);
	    }

	    parser->~Parser();*/


	//comienzo a mandar info
	cout << "HAGO TODO LO QUE TENGA QUE HACER EL HANDSHAKE" << endl;
	//MANDO DIMENSIONES DE VENTANA.
	msg.tipo=HANDSHAKE_DIMENSIONES_VENTANA;
	msg.objectId="X0";
	msg.message="900x600";
	colaCliente->push(msg);
	//---------------------------------------------

	//MANDAR SPRITES
	//DEBE DE ITERAR ENTRE TODOS LOS SPRITES
	msg.tipo=HANDSHAKE_SPRITES;
	msg.objectId="primerFondo";
	// RESOLUCION DEL OBJETO, PARA ESCALAR LA IMAGEN SI ES NECASARIO
	// VER SI ES NECESARIO PASARLE LA CANT DE FOTOGRAMAS TMB
	// ANCHO;ALTO
	msg.message="0;0";
	colaCliente->push(msg);

	msg.objectId="fondoUno";
	msg.message="0;0";
	colaCliente->push(msg);

	msg.objectId="fondoDos";
	msg.message="0;0";
	colaCliente->push(msg);

	msg.objectId="barra8";
		msg.message="0;0";
		colaCliente->push(msg);

		msg.objectId="fondoTres";
			msg.message="0;0";
			colaCliente->push(msg);

			msg.objectId="foo";
			msg.message="0;0";
			colaCliente->push(msg);

	// -------------------------------

	//MANDAR OBJETOS NUEVOS
	//INVENTAR ID
		/*msg.tipo=HANDSHAKE_OBJETO_NUEVO;
		msg.objectId="F01";
		msg.message="primerFondo;0;0";
		colaCliente->push(msg);*/

		msg.tipo=HANDSHAKE_FONDO_NUEVO;
		msg.objectId="F02";
		msg.message="fondoUno;0;0";
		colaCliente->push(msg);

		msg.tipo=HANDSHAKE_FONDO_NUEVO;
		msg.objectId="F03";
		msg.message="fondoDos;0;0";
		colaCliente->push(msg);


		msg.tipo=HANDSHAKE_OBJETO_NUEVO;
				msg.objectId="F01";
				msg.message="barra8;0;0";
				colaCliente->push(msg);
				msg.tipo=HANDSHAKE_FONDO_NUEVO;
							msg.objectId="F04";
							msg.message="fondoTres;0;0";
							colaCliente->push(msg);

	msg.tipo=HANDSHAKE_OBJETO_NUEVO;
	msg.objectId="J1";
	msg.message="foo;0;0";
	colaCliente->push(msg);
	//---------------------------------

    //FIN DE HANDSHAKE.
	msg.tipo=FIN_HANDSHAKE;
	msg.objectId="X0";
	msg.message="termino el handshake";
	colaCliente->push(msg);

	createTimerThread();
}


int Servidor::enviarChat(mensajeStruct msg){
	int idCliente = contenedor->getUsuarioBySocket(msg.socketCli)->getIdUsuario();
    list<int> otroUsuarios = contenedor->getIdOtrosUsuarios(idCliente);
	
	chatStruct chat;
	chat.message = msg.message;
	chat.from = idCliente; //CAMBIAR POR EL ID DE USUARIO!
	//chat.to = msg.otherCli;

	list<int>::iterator it=otroUsuarios.begin();
	if (chat.to == 99){ // si quiere enviar a todos los usuarios
		for(it ; it != otroUsuarios.end();it++){
			waitingChats.insert(pair<int,chatStruct>(*it,chat));
		}
	}else {//ENVIA MENSAJE A UN SOLO USUARIO
		waitingChats.insert(pair<int,chatStruct>(chat.to,chat));
	}
		
	return 0;
}
int Servidor::procesarDesconexion(mensajeStruct mensaje){
	queue<mensajeStruct>* colaCliente = socketIdQueue[mensaje.socketCli];
	colaCliente->push(mensaje);

	return 0;
}
int Servidor::recibirTodosLosChats(mensajeStruct msgPedido){
	int socketCli = msgPedido.socketCli;
	int idCliente = contenedor->getUsuarioBySocket(socketCli)->getIdUsuario();
	queue<mensajeStruct>* colaCliente = socketIdQueue[msgPedido.socketCli];

	mensajeStruct msj;

	multimap<int,chatStruct>::iterator elemento;

	while (!((elemento = waitingChats.find(idCliente)) == waitingChats.end())){
		enviarMensajeSegmentado(socketCli, &(elemento->second), colaCliente);
		waitingChats.erase (elemento);
	}

	msj.socketCli = socketCli;//socket del que recibe los msjs
	msj.objectId = "00";
	msj.message = "Fin de chats";
	msj.tipo = RECIBIR_CHATS_LISTO;
	colaCliente->push(msj);

	return 0;
}

int Servidor::enviarMensajeSegmentado(int socketCli, chatStruct* chat, queue<mensajeStruct>* colaCliente ){

	string buf;
	int pini=0;

	string input = chat->message;
	int lengthInput = strlen(input.c_str());

	mensajeStruct mensaje;
	//mensaje.otherCli = chat->from;
	mensaje.socketCli = socketCli;

	while(lengthInput>MAXDATASIZE){
		buf = input.substr(pini,MAXDATASIZE);
		pini+=MAXDATASIZE;
		lengthInput -= MAXDATASIZE;
		//ENVIAR MENSAJE SIGUIENTE
		mensaje.tipo = RECIBIR_CHAT_SIGUE;
		mensaje.message = buf;
		colaCliente->push(mensaje);
	}
	if (lengthInput!=0){
		buf= input.substr(pini,lengthInput);
		//ENVIAR MENSAJE CON FIN
		mensaje.tipo = RECIBIR_CHAT_FIN;
		mensaje.message=buf;
		colaCliente->push(mensaje);
	}

	return 0;
}

int Servidor::openSocket(short puerto){
	int conexiones_max = 10;
	int yes=1;

	if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR abriendo el socket \n");
		Log::log('s',3,"Abriendo el socket","");
		return 1;
	}
	if (setsockopt(this->sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("ERROR ejecutando setsockopt \n");
		Log::log('s',3,"Ejecutando setsockopt","");
		return 1;
	}
	this->my_addr.sin_family = AF_INET;
	this->my_addr.sin_port = htons(puerto);
	this->my_addr.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
	memset(&(this->my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura
	if (bind(this->sockfd, (struct sockaddr *)&this->my_addr, sizeof(struct sockaddr)) == -1) {
		perror("ERROR ejecutando bind \n");
		Log::log('s',3,"Ejecutando bind","");
		return 1;
	}

	if (listen(this->sockfd, conexiones_max) == -1) {
		perror("ERROR ejecutando listen \n");
		Log::log('s',3,"Ejecutando listen","");
		return 1;
	}
	return 0;
}

void* Servidor::recibirMensajesCliente(void* arguments){
	argsForThread* args = (argsForThread*) arguments;
	int socketCli = *(args->socketCli);
	int finish = 0;

   mensajeStruct mensaje;
   string mensajeParcial = "";
   bool hayMsjParcial = false;

   //Receive a message from client
   while(finish == 0){
	   mensaje = {}; //Reset struct

	   finish = args->context->mensajeria.receiveAndDecode(socketCli,&mensaje);

	   if (mensaje.tipo == DISCONNECTED){
		   cout << "Usuario Desconectado" << endl;
		   args->context->contenedor->cerrarSesion(socketCli);
		   args->context->colaPrincipalMensajes.push(mensaje);
		   args->context->cantCon--;
	   }else if (mensaje.tipo == ENVIAR_CHAT_SIGUE){
		   //si ya existia concateno el mensaje
		   mensajeParcial += mensaje.message;
		   hayMsjParcial = true;
	   }else{
		   if (hayMsjParcial && !finish){
			   //primero concateno el mensaje y después lo asigno
			   mensajeParcial += mensaje.message;
			   mensaje.message = mensajeParcial;
		   }
		   //agrego a la cola principal
		   //mutex lock.
			if (SDL_LockMutex(mutexQueue) == 0) {
			   args->context->colaPrincipalMensajes.push(mensaje);
			   hayMsjParcial = false;
		   	   mensajeParcial = "";
			   //mutex unlock
			   SDL_UnlockMutex(mutexQueue);
			}
	   }
   }
   //MARCAR USER COMO DESCONECTADO
   //delete((argsForThread*) arguments); //asegurarnos que esto no hace explotar al mundo
   close(socketCli);

   return 0;
}

void *Servidor::sendMessage(void *arguments){

 	argsForThread* args = (argsForThread*) arguments;
	int socketCli = *(args->socketCli);
	bool finish=false;
	int result=0;
	stringstream idSocket;
	queue<mensajeStruct>* queueCli=args->context->socketIdQueue[socketCli];

    
    	while(!finish){
		    if(!queueCli->empty()){
		    	mensajeStruct* msg = new mensajeStruct();
		    	*msg=queueCli->front();
		    	queueCli->pop();
		    	if(msg->tipo == DISCONNECTED){
		    		finish = true;
		    	}else{

					result=args->context->encodeAndSend(socketCli,msg);
					idSocket <<  msg->socketCli;
					Log::log('s',1,"Respondiendo mensaje al cliente: " +idSocket.str(), msg->message);
					finish = (result != 0);
				}
		    	delete(msg);
			//free(&msg);
		    }
		
    	}

	return 0;
}


void Servidor::nuevaConexion(int new_fd) {
	struct timeval timeout;
	timeout.tv_sec = 180;
	timeout.tv_usec = 0;
	pthread_t precvMessage;
	pthread_t psendMessage;
	Jugador *jugador = new Jugador(1,5,50,400,1,1);
	this->escenario->addJugador(jugador);
	if (setsockopt (new_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		Log::log('s',3,"Seteando el rcv timeout","");
	//	printf("ERROR seteando el rcv timeout \n");
	if (setsockopt (new_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		Log::log('s',3,"Seteando el snd timeout","");
	//	printf("ERROR seteando el snd timeout \n");
	//CREO LA COLA DE CLIENTE Y GUARDO EN UN MAP
 	queue<mensajeStruct> * queueClient =new queue<mensajeStruct>;
	socketIdQueue[new_fd]= queueClient;

	arguments->context = this;
	arguments->socketCli = &new_fd;

	int rc = pthread_create(&precvMessage, NULL, recibirMensajesCliente, (void*)arguments);
	pthread_detach(precvMessage);
	if (rc){
	//	printf("ERROR creando el thread de recv %i \n",rc);
		Log::log('s',3,"Creando el thread de recv","");
	}

	rc = pthread_create(&psendMessage, NULL, sendMessage, (void*)arguments);
	pthread_detach(psendMessage);
	if (rc){
		//printf("ERROR creando el thread de send %i \n",rc);
		Log::log('s',3,"Creando el thread de send","");
	}
	//delete args;

}

int Servidor::escuchar() {
	socklen_t sin_size;
	int new_fd;
	struct sockaddr_in their_addr; // información sobre la dirección del cliente

	mensajeStruct messageAccept;

	while(!this->cerrarPrograma) { // main accept() loop
		sin_size = sizeof(struct sockaddr_in);
		new_fd = accept(this->sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
		//	perror("ERROR ejecutando accept \n");
			Log::log('s',3,"Ejecutando accept","");
			continue;
		}

		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		Log::log('s',1,"server: got connection from " + string(inet_ntoa(their_addr.sin_addr)),"");
		
		messageAccept.socketCli = new_fd;
		messageAccept.objectId = "00";
		if (cantCon == MAX_CON){
			messageAccept.tipo = CONECTAR_NOTOK;
			messageAccept.message = "ERROR: Supera cantidad maxima de conexiones";
			mensajeria.encodeAndSend(new_fd,&messageAccept);
			close(new_fd);
		}else{
			messageAccept.tipo = CONECTAR_OK;
			messageAccept.message = "Se puede conectar";
			mensajeria.encodeAndSend(new_fd,&messageAccept);

			cantCon ++;
			nuevaConexion(new_fd);
		}
	}
	return 0;
}


short getPuerto(){
	short inputPuerto;
	bool ok = false;

	cout << "Ingrese el puerto del servidor:" << endl;
	while (!ok){
		cin >> inputPuerto;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
			Log::log('s',3,"Numero ingresado incorrecto","");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}else
			ok = true;
	}

	return inputPuerto;

}

string getCSVPath(){
	string path;

	cout << "Ingrese el nombre del archivo CSV ('d' para default):" << endl;
	cin >> path;

	if (path == "d"){
		return "usuarios.csv";
	}else{
		return path;
	}
}


void Servidor::runServer(){
	cout << "Starting server app" << endl;
	Log::log('s',1,"Starting server app","");
	mutexQueue = SDL_CreateMutex();
	this->cerrarPrograma = false;
	this->threadExit = 0;
	this->threadMain= 0;
	this->threadTimer= 0;

	short puerto = getPuerto();

	string pathCSV = getCSVPath();
	this->contenedor->inicializarContenedor(pathCSV);

	createExitThread();
	createMainProcessorThread();

	openSocket(puerto);
	escuchar();

	terminarThreads();
};

int Servidor::terminarThreads(){
	pthread_join(this->threadExit, NULL);
	pthread_join(this->threadMain, NULL);
	pthread_join(this->threadTimer, NULL);

	return 0;
}


void* Servidor::exitManager(void* context) {
	  string input;
	  bool quit = false;
	  Servidor* contexto = (Servidor*)context;
	  mensajeStruct mensajeExit;
	  mensajeExit.tipo = DISCONNECTED;
	  mensajeExit.objectId = "00";
	  mensajeExit.message = "El servidor se cerro";

	  cout << "Escribe 'quit' en cualquier momento para salir" << endl;
	  while (!quit){
		  getline (cin, input);
		  quit = (input == "quit");
	  }

	  printf("Saliendo de la aplicación...\n");
	  printf("Cerrando el socket...\n");

	  shutdown(contexto->sockfd, SHUT_RDWR);
	  close(contexto->sockfd);
	  contexto->cerrarPrograma = true;

	  for(auto const &user :  contexto->contenedor->socket_usuario) {
		  if(user.second->isConectado()){
			  mensajeExit.socketCli = user.second->getIdSocket();
			  contexto->mensajeria.encodeAndSend(user.second->getIdSocket(),&mensajeExit);
		  }
	  	}

	  //todos los sockets: enviar mensaje de desconexion


	  printf("Aplicación finalizada\n");
	  Log::log('s',1,"Aplicación finalizada","");
	  //exit(0);
	  return 0;

}

void Servidor::createExitThread(){
	int rc = pthread_create(&this->threadExit, NULL,&Servidor::exitManager, this);
	if (rc){
		printf("ERROR creando el thread de salida %i \n",rc);
		Log::log('s',3,"creando el thread de salida","");
	}
}

void Servidor::createMainProcessorThread(){
	int rc = pthread_create(&this->threadMain, NULL,&Servidor::procesarMensajesMain, this);
	if (rc){
		printf("ERROR creando el thread de procesamiento principal %i \n",rc);
		Log::log('s',3,"Creando el thread de procesamiento principal","");
	}
}

void Servidor::createTimerThread(){
	cout <<  "createTimerThread" << endl;
	int rc = pthread_create(&this->threadTimer, NULL,&Servidor::manejarTimer, this);
	if (rc){
		printf("ERROR creando el thread del timer %i \n",rc);
		Log::log('s',3,"Creando el thread del timer","");
	}
}

void* Servidor::manejarTimer (void *data) {
	Servidor* context = (Servidor*)data;

	while (1){
		context->escenario->aceptarCambios();
		usleep(10000);
	}
}



Servidor::Servidor() {
	this->contenedor = new ContenedorUsuarios();
	this->arguments = new argsForThread();
	this->escenario = new EscenarioS(800,600);
}
Servidor::~Servidor() {
	delete this->contenedor;
	delete this->arguments;
	delete this->escenario;
	map<int,queue<mensajeStruct>*>::iterator it;

	for(it = this->socketIdQueue.begin(); it != this->socketIdQueue.end(); it++) {
		delete it->second;
	}

}
