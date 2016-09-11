#include "Servidor.h"
#include "../Common/Mensajeria.h"
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <sstream>
#include <string>



struct argsForThread{
	int* socketCli;
	Servidor* context;
};


using namespace std;

//#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez




void* Servidor::procesarMensajesMain (void *data) {
	mensajeStruct msg;
	Servidor* context = (Servidor*)data;
	bool finish = false;
	int result;

   

	while(!finish){
		//si la cola está vacia. 
		if (context->colaPrincipalMensajes.empty()){
			
		}else{			
			msg=context->colaPrincipalMensajes.front();
			context->colaPrincipalMensajes.pop();
			printf("Procesando Mensaje: %s",msg.message.c_str());
			result = context->procesarMensajeCola(msg);
			finish = (result != 0);
		}
	}

	return 0;

}

int Servidor::loginInterpretarMensaje(mensajeStruct msg){
	printf("LLEGOOO\n");

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
		
	}

	return 0;
}

int Servidor::enviarChat(mensajeStruct msg){
	chatStruct chat;
	chat.from = msg.socketCli; //CAMBIAR POR EL ID DE USUARIO!
	chat.to = msg.otherCli;
	chat.message = msg.message;

	waitingChats.insert(pair<int,chatStruct>(chat.to,chat));
	return 0;
}

int Servidor::recibirTodosLosChats(mensajeStruct msg){
	int idCliente = msg.socketCli;
	mensajeStruct msj;

	multimap<int,chatStruct>::iterator elemento;

	while (!((elemento = waitingChats.find(idCliente)) == waitingChats.end())){
		msj.socketCli = msg.socketCli; //socket del que recibe los msjs
		msg.otherCli = elemento->second.from;
		msg.message = elemento->second.message;
		waitingChats.erase (elemento);
		//TODO: AGREGAR A COLA DE CLIENTE
	}

	return 0;
}


int Servidor::openSocket(short puerto){
	int conexiones_max = 10;
	int yes=1;

	if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR abriendo el socket \n");
		return 1;
	}
	if (setsockopt(this->sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("ERROR ejecutando setsockopt \n");
		return 1;
	}
	this->my_addr.sin_family = AF_INET;
	this->my_addr.sin_port = htons(puerto);
	this->my_addr.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
	memset(&(this->my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura
	if (bind(this->sockfd, (struct sockaddr *)&this->my_addr, sizeof(struct sockaddr)) == -1) {
		perror("ERROR ejecutando bind \n");
		return 1;
	}

	if (listen(this->sockfd, conexiones_max) == -1) {
		perror("ERROR ejecutando listen \n");
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
	   cout << mensaje.message << endl;

	   if (mensaje.tipo == ENVIAR_CHAT_SIGUE){
		   //si ya existia concateno el mensaje
		   mensajeParcial += mensaje.message;
		   hayMsjParcial = true;
	   }else{
		   if (hayMsjParcial){
			   //primero concateno el mensaje y después lo asigno
			   mensajeParcial += mensaje.message;
			   mensaje.message = mensajeParcial;
		   }
		   //agrego a la cola principal
		   printf("Cola principal con ID: %d", args->context->colaPrincipal);
		   args->context->colaPrincipalMensajes.push(mensaje);
		   hayMsjParcial = false;
		   mensajeParcial = "";
	   }
   }

   close(socketCli);

   return 0;
}


void sigchld_handler(int s) {
	while(wait(NULL) > 0);
}

void *sendMessage(void *nw_fd){
	/*
	int new_fd = *(int *)nw_fd;
	char buf[20] = "Recibido.Cambio";
	send(new_fd, buf , 20, 0);*/
	return 0;
}
/*
void *recvMessage(void *nw_fd){
	
	//ACA DEBERIA DE IR EL COMPORTAMIENTO DEL SERVER EN FUNCION AL ID DEL MENSAJE ( VALIDAR USARIO, MANDAR MENSAJES AL CLIENTES ..)


	int new_fd = *(int *)nw_fd;
	while(true){	
	char buf[30]= "";
	recv(new_fd, buf, 30, 0);
	cout << "el cliente "<< new_fd <<" dice : " ;
	cout << buf << endl;
	}
	return 0;
}*/


void Servidor::nuevaConexion(int new_fd) {

	struct timeval timeout;
	timeout.tv_sec = 60;
	timeout.tv_usec = 0;
	pthread_t precvMessage;
	pthread_t psendMessage;
	
	if (setsockopt (new_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		printf("ERROR setealdo el rcv timeout \n");
	if (setsockopt (new_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		printf("ERROR setealdo el snd timeout \n");
	int cola_socket;
	mensajeria.crearCola(cola_socket); //TODO: AGREGAR ESTO A LOS DATOS DEL USER

	argsForThread* args = new argsForThread();
	args->context = this;
	args->socketCli = &new_fd;

	int rc = pthread_create(&precvMessage, NULL, recibirMensajesCliente, (void*)args);
	if (rc){
		printf("ERROR creando el thread de recv %i \n",rc);
	}

	rc = pthread_create(&psendMessage, NULL, sendMessage, (void*)args);
	if (rc){
		printf("ERROR creando el thread de send %i \n",rc);
	}

	//delete args;

}

int Servidor::escuchar() {
	socklen_t sin_size;
	int new_fd;
	struct sockaddr_in their_addr; // información sobre la dirección del cliente

	mensajeStruct messageAccept;

	while(1) { // main accept() loop
		sin_size = sizeof(struct sockaddr_in);
		new_fd = accept(this->sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("ERROR ejecutando accept \n");
			continue;
		}

		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		
		messageAccept.socketCli = new_fd;
		messageAccept.otherCli = 0;
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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}else
			ok = true;
	}

	return inputPuerto;

}


void Servidor::runServer(){
	cout << "Starting server app" << endl;

	short puerto = getPuerto();
	createExitThread();
	createMainProcessorThread();

	openSocket(puerto);
	escuchar();

};


void* Servidor::exitManager(void* context) {
	  string input;
	  bool quit = false;

	  cout << "Escribe 'quit' en cualquier momento para salir" << endl;
	  while (!quit){
		  getline (cin, input);
		  quit = (input == "quit");
	  }

	  printf("Saliendo de la aplicación...\n");
	  printf("Cerrando el socket...\n");

	  close(((Servidor*)context)->sockfd);
	  //todos los sockets: enviar mensaje de desconexion


	  printf("Aplicación finalizada\n");
	  exit(0);

}

void Servidor::createExitThread(){
	pthread_t threadExit;

	int rc = pthread_create(&threadExit, NULL,&Servidor::exitManager, this);
	if (rc){
		printf("ERROR creando el thread de salida %i \n",rc);
	}
}

void Servidor::createMainProcessorThread(){
	pthread_t threadMain;

	int rc = pthread_create(&threadMain, NULL,&Servidor::procesarMensajesMain, this);
	if (rc){
		printf("ERROR creando el thread de procesamiento principal %i \n",rc);
	}
}

Servidor::Servidor() {

}
Servidor::~Servidor() {

}
