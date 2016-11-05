#include "Cliente.h"
#include "../Common/Log.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <string.h>

#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "Escenario.h"
#include <chrono>


//using namespace std;

//#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez
#define LOREMIPSUM "Cliente/loremIpsum.txt"


Cliente::Cliente() {

}

Cliente::~Cliente() {
	this->escenario.close();
}


int Cliente::seleccConectar(){
	int respuesta = 1;
	string usuario, contrasenia;

	if (this->datosConexion.conectado){

		cout << "El usuario ya está conectado" << endl;
		Log::log('c',1,"El usuario " + usuario + " ya está conectado","");
		respuesta = 0;

	}else{

		getUsuarioYContrasenia(usuario, contrasenia);
		respuesta = 0;

		this->mapIdNombreUsuario = conectar(&this->datosConexion, usuario, contrasenia);

		if (!this->mapIdNombreUsuario.empty()){
			Log::log('c',1,"Usuario " + usuario + " logueado correctamente","");
			this->datosConexion.conectado = true;

			//EVENTUALMENTE EL HILO SE CREA CON EL METODO RECV&DECODE
			int rc = pthread_create(&this->threadRecv, NULL,&recvMessage,(void*)this);
			if (rc){
				Log::log('c',1,"creando el thread de recibir mensajes","");
			}

			//Envio mensaje para comenzar el handshake
			handshake(&datosConexion);

			int rv = pthread_create(&this->threadEscenario, NULL,&crearEscenario,(void*)this);
			if (rv){
				Log::log('c',1,"creando el thread escenario","");
			}
			/*
			//Creo hilo para escuchar los eventos del teclado
			int rg=pthread_create(&this->threadRecv,NULL,&handleKeyEvents,(void*)this);
			if (rg){
							Log::log('c',1,"creando el thread de handleEvents","");
				}*/
			respuesta = 0;
		}else{
			cerrarSocket(this->datosConexion.sockfd);
			respuesta = 1;
			Log::log('c',1,"Usuario " + usuario + " no pudo iniciar sesion","");
		}
	}


	return respuesta;
}
bool Cliente::handleKeyEvents(){
    //Event handler
    SDL_Event e;
    bool salir=false;
    string accion = "NADA";
    auto start_time = chrono::high_resolution_clock::now();
    bool timer = false;;
    mensajeStruct evento;
    evento.tipo=PULSA_TECLA;
    evento.objectId="X0";
    evento.socketCli= this->datosConexion.sockfd;

	while( SDL_PollEvent( &e ) != 0 ) {
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			cout << "quit event"<< endl;
			salir=true;
			this->jugando = false;
		    evento.tipo=DISCONNECTED;
		}
		//User presses a key
		else{

			if (this->escenario.esperandoJugadores){
			 if ( e.type == SDL_KEYUP && e.key.repeat == 0 ){
				 switch( e.key.keysym.sym ){
					case SDLK_LEFT:
						this->vecesX += 1;
						break;
					case SDLK_RIGHT:
						this->vecesX -= 1;
						break;
				}
			}

			if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
				switch( e.key.keysym.sym ){
					case SDLK_LEFT:
						this->vecesX -= 1;
						break;
					case SDLK_RIGHT:
						this->vecesX += 1;
						break;
					case SDLK_UP:
						accion = "SALTA";
						break;
					case SDLK_r:
						this->vecesX = 0;
						accion = "RESET";
						break;
					case SDLK_a:
						accion = "DISPARO";
					    break;
				}
			}

		}
		}

	}
	if (this->escenario.esperandoJugadores){
	evento.message=convertirAString(vecesX) + ";" + accion;
	}else{
		evento.message="0;NADA";
	}
	//SDL_Delay(1);

	while(!timer){
		auto end_time = chrono::high_resolution_clock::now();
		if(chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() >= 2000	){
			timer=true;
		}
	}
	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_KEYUP);

	if (enviarEvento(&evento)==1){
		//hubo error en el send
		cout << "SERVIDOR DESCONECTADO" << endl;
		salir = true;
		this->jugando = false;
	}

	return salir;
}


string Cliente::convertirAString(int i) {
	stringstream iS;
	iS << i;
	return iS.str();
}
void *Cliente::recvMessage(void * arg){

	bool finish = false;
	Cliente* context = (Cliente*)arg;
	string mensajeParcial = "";
	//bool hayMsjParcial = false;
	mensajeStruct mensajeRta;
	string nombre;
	//string mensajeAMostrar;

	while(!finish){
		finish = context->conexionCli.recibirMensaje(&context->datosConexion, &mensajeRta);
		Log::log('c',1,"Mensaje recibido: " ,mensajeRta.message);

		switch (mensajeRta.tipo){
			/*case RECIBIR_CHAT_SIGUE:
			   //si ya existia concateno el mensaje
			   mensajeParcial += mensajeRta.message;
			   hayMsjParcial = true;
			   break;
			case RECIBIR_CHAT_FIN:
				if (hayMsjParcial && !finish){
				   //primero concateno el mensaje y después lo asigno
				   mensajeParcial += mensajeRta.message;
				   mensajeRta.message = mensajeParcial;
				   mensajeParcial = "";
				}
				//nombre = context->getNombreUsuarioById(mensajeRta.otherCli);
				mensajeAMostrar = nombre + " escribió: " + mensajeRta.message + "\n";
				printf("\n %s \n",mensajeAMostrar.c_str());
				break;
			case RECIBIR_CHATS_LISTO: //Terminé de recibir todos los mensajes
				context->semaforoReceive = false;
				break;*/
			case HANDSHAKE_DIMENSIONES_VENTANA:
				context->setDimensionesVentana(mensajeRta);
				break;
			case HANDSHAKE_SPRITES:
				context->addSprite(mensajeRta);
				break;
			case HANDSHAKE_SPRITE_NRO:
				context->createNro(mensajeRta);
				context->escenario.crearContador("1");
				break;
			case HANDSHAKE_ESTADO_SPRITE:
				context->addEstadoSprite(mensajeRta);
				break;
			case HANDSHAKE_OBJETO_NUEVO:
				context->objetoNuevo(mensajeRta);
				break;
			case HANDSHAKE_FONDO_NUEVO:
				context->objetoNuevo(mensajeRta);
				break;
			case FIN_HANDSHAKE:
				cout << "Fin del handshake" << endl;
				context->escenarioOK=true;
				break;
			case ESCENARIO_UPD:
				if (context->jugando) context->escenario.moverFondo(mensajeRta);
				break;
			case JUGADOR_SO_VO:
				context->escenario.crearJugadorPrincipal(mensajeRta);
				break;
			case JUEGO_COMENZAR:
				context->escenario.esperandoJugadores=true;
				break;
			case JUGADOR_UPD:
				if (context->jugando) context->updateJugador(mensajeRta);
				break;
			case ENEMIGO_NEW:
				context->objetoNuevo(mensajeRta);
				break;
			case ENEMIGO_UPD:
				if (context->jugando) context->updateEnemigo(mensajeRta);
				break;
			case ENEMIGO_DELETE:
				context->escenario.eliminarObjeto(mensajeRta.objectId);
				break;
			case BALA_UPD:
				if (context->jugando) context->updateBala(mensajeRta);
				break;
			case DISCONNECTED:
				context->datosConexion.conectado = false;
				context->conexionCli.cerrarSocket(context->datosConexion.sockfd);
				context->printMenu();
				context->imprimirConsigna();
				break;
			case RESET:
				context->vecesX=0;
				context->jugando=false;
				context->escenarioOK=false;
				while(context->escenario.running){}
				context->handshake(&context->datosConexion);
				break;
		}
    }
	return 0;
};


void Cliente::objetoNuevo(mensajeStruct msg){
	vector<string> result = Util::Split(msg.message,';');
	estadoJugador estado = PARADO;
	string conectado = "C";

	string spriteId = result[0];
	int x=atoi(result[1].c_str());
	int y=atoi(result[2].c_str());
	if (result.size() > 3){
		 estado = static_cast<estadoJugador>(atoi(result[3].c_str()));
	 	 conectado = result[4];
	}

	escenario.crearObjeto(msg.objectId,spriteId,x,y,estado,conectado);

	if (msg.tipo == HANDSHAKE_FONDO_NUEVO) {
		escenario.addFondo(msg.objectId);
	}

}

void Cliente::updateEnemigo(mensajeStruct msg){
	vector<string> result = Util::Split(msg.message,';');

	int x=atoi(result[0].c_str());
	int y=atoi(result[1].c_str());

	escenario.actualizarEnemigo(msg.objectId,x,y);
}

void Cliente::updateBala(mensajeStruct msg){
	vector<string> result = Util::Split(msg.message,';');

	string spriteId = result[0];
	int x=atoi(result[1].c_str());
	int y=atoi(result[2].c_str());

	//escenario.crearOActualizarEnemigo(msg.objectId,spriteId,x,y);
	escenario.actualizarEnemigo(msg.objectId,x,y);
}


void Cliente::updateJugador(mensajeStruct msg){
	int x,y;
	string conectado;
	estadoJugador estado;
	vector<string> result = Util::Split(msg.message, ';');
	x=atoi(result[0].c_str());
	y=atoi(result[1].c_str());
	//estado jugador
	estado = static_cast<estadoJugador>(atoi(result[2].c_str()));
	conectado =result[3] ;
	escenario.actualizarPosicionObjeto(msg.objectId,x,y,estado,conectado);

	escenario.contadores["1"]->actualizarPuntaje(1);
}


void Cliente::createNro(mensajeStruct msg){
	int ancho, alto;
	string separador = ";";
	string strAux;
	int pos = msg.message.find(separador);

	strAux = msg.message.substr(0,pos);
	ancho = atoi(strAux.c_str());
	strAux = msg.message.substr(pos+1,msg.message.length());
	alto = atoi(strAux.c_str());

	this->escenario.crearNumero(msg.objectId, ancho, alto);

}


void Cliente::addSprite(mensajeStruct msg){
	int ancho, alto;
	string separador = ";";
	string strAux;
	LTexture* textura;
	int pos = msg.message.find(separador);

	strAux = msg.message.substr(0,pos);
	ancho = atoi(strAux.c_str());
	strAux = msg.message.substr(pos+1,msg.message.length());
	alto = atoi(strAux.c_str());
	textura = this->escenario.addSprite(msg.objectId, ancho, alto);
}


void Cliente::addEstadoSprite(mensajeStruct msg){
	vector<string> result = Util::Split(msg.message,';');
	estadoJugador estado = static_cast<estadoJugador>(atoi(result[0].c_str()));
	int anchoFrame = atoi(result[1].c_str());
	int altoFrame = atoi(result[2].c_str());
	int cantFrame = atoi(result[3].c_str());
	int ordenEstado = atoi(result[4].c_str());
	this->escenario.agregarEstado(msg.objectId, estado,anchoFrame,altoFrame,cantFrame,ordenEstado);
}


void Cliente::setDimensionesVentana(mensajeStruct msg){
	int x,y;
	string separador = "x";
	string dimension;
	int pos = msg.message.find(separador);

	dimension = msg.message.substr(0,pos);
	x=atoi(dimension.c_str());
	dimension = msg.message.substr(pos+1,msg.message.length());
	y=atoi(dimension.c_str());

	this->escenario.setDimensiones(x,y);
}

 void* Cliente::crearEscenario(void *arg){
	 bool salir=false;
	 Cliente* context = (Cliente*)arg;

	 while (!salir){
		 while(!context->escenarioOK){
		 }
		 context->jugando = true;
		 context->escenario.init();
		 if ( !context->escenario.loadMedia() ) {
			 // Aca deberia salir del programa, xq no se pudo
			 // cargar alguna imagen (ni siquiera la img por defecto)
			 return NULL;
		 }
		 context->escenario.calcularParallax();

		SDL_FlushEvent(SDL_KEYDOWN);
		SDL_FlushEvent(SDL_KEYUP);
		 while(context->jugando){

			// if(context->escenario.esperandoJugadores){
				 salir=context->handleKeyEvents();
			//	 }
			 if(context->jugando) {
				 context->escenario.renderizarObjetos();

			 }

			// if(!context->escenario.esperandoJugadores){
				// cout << "esta renderizando pausa" << endl;


				 //				 }
		 }
		 context->escenario.close();
	 }
	 context->salir();

	 return 0;
};

int Cliente::getUsuarioYContrasenia(string &usuario, string &contrasenia){
	string inputUsuario, inputContrasenia;
	bool ok = false;

	while (!ok){
		cout << "Ingrese el nombre de usuario:" << endl;
		cin >> usuario;
		if (usuario.find(";") == string::npos)
			ok = true;
	}

	ok = false;
	while (!ok){
		cout << "Ingrese la contraseña:" << endl;
		cin >> contrasenia;
		if (contrasenia.find(";") == string::npos)
			ok = true;
	}

	return 0;
}

void Cliente::terminarThreadRecv(){
	if (this->threadRecv != 0) {
		// Espero a que termine el threadRecv
		pthread_join(this->threadRecv, NULL);
		this->threadRecv = 0;
	}
}

int Cliente::seleccDesconectar(){
	int respuesta = 0;

	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado" << endl;
		// Por que capaz la desconexion la hizo el server
		terminarThreadRecv();
		return 0;
	}

	cout << "Desconectando..." << endl;
	respuesta = desconectar(&this->datosConexion);
	terminarThreadRecv();
	if (respuesta == 0){
		this->datosConexion.conectado = false;
		Log::log('c',1,"Usuario cerro sesion","");
	}


	return respuesta;
}

int Cliente::salir(){
	seleccDesconectar();
	Log::log('c',1,"El usuario salio del programa","");
	return -1;
}

int Cliente::enviar(){
	int usuario = 0;
	string mensaje = "";
	stringstream idUsuario;

	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado, no puede enviar mensajes." << endl;
		Log::log('c',2,"El usuario no está conectado, no puede enviar mensajes","");
	}else{
		ingresarUsuarioYMensaje(&usuario,&mensaje);
		idUsuario << usuario;
		enviarMensajes(&this->datosConexion,usuario,mensaje);
		Log::log('c',1,"Mensaje enviado a usuario: " + idUsuario.str() ,mensaje);
	}
	return 0;
}

int Cliente::ingresarUsuarioYMensaje(int* idUsuario, string* mensaje){
	bool ok = false;
	int usuario;
	string inputMsj;
	cout << "----------------------" << endl;
	cout << "ID - Nombre Usuario" << endl;
	cout << "----------------------" << endl;
	for(auto const &user : mapIdNombreUsuario) {
		cout << user.first << " - " << user.second << endl;
	}
	cout << "99 - Enviar a todos" << endl;
	cout << "----------------------" << endl;
	cout << endl;
	cout << "Ingrese el id del destinatario:" << endl;
	while (!ok){
		cin >> usuario;
		if (!datosConexion.conectado){
			return 0;
		}else if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
		}else if((usuario != 99) && (mapIdNombreUsuario.find(usuario) == mapIdNombreUsuario.end())){
			cout << "Error: Ingrese un id válido" << endl;
		}else{
			ok = true;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if (datosConexion.conectado){
		cout << endl;
		cout << "Inserte el Mensaje a Enviar: "<< endl;
		getline (cin,inputMsj);
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		*idUsuario = usuario;
		*mensaje = inputMsj;
	}
	return 0;
}

int Cliente::recibir(){

	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado, no puede recibir mensajes" << endl;
		Log::log('c',2,"El usuario no está conectado, no puede recibir mensajes,","");
		return 0;
	}

	conexionCli.pedirMensajes(&datosConexion);
	semaforoReceive = true;
	while (semaforoReceive){}

	return 0;
}

/*int Cliente::loremIpsum(){
	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado. Opción inválida." << endl;
		return 0;
	}

		list<int> clientes = getIdUsuarios();
		int numCli;
		srand(unsigned(time(0)));
		numCli = (rand()%clientes.size());

		list<int>::iterator it=clientes.begin();
		advance(it,numCli);
		int idCliente=*it;
		cout << "los mensajes se envian a : " << idCliente<< endl;
		int tamanio;
		srand(unsigned(time(0)));
		tamanio = rand()%200+1;

		int frecuencia;
		int cantMax;
		int milisegundos;
		string linea;
		string linea_aux;
		string linea_aux2;
		string linea_final;
		int tamanio_aux=0;
		int pos;
		cout << "Frecuencia de envio:";
		cin >> frecuencia;
		cout << "Cantidad maxima de mensajes:";
		cin >> cantMax;
		milisegundos= 1000000/frecuencia;
		int cont = 1;

	   while((cont <= cantMax) && (this->datosConexion.conectado)){
		fstream file2(LOREMIPSUM,ios::in | ios::out | ios::app);
		if (!file2.is_open()){
			  perror("Error apertura de archivo");
		}
		while (!file2.eof() && (cont <= cantMax ) && (this->datosConexion.conectado)){
			getline(file2, linea);
			pos=0;

			 while(((pos+tamanio)<= linea.length()) && (cont <= cantMax) && (this->datosConexion.conectado)){
			           linea_aux2 = linea.substr(pos,tamanio - tamanio_aux);
			           linea_final = linea_aux + linea_aux2;

			           linea_aux = "";
			           linea_aux2 = "";


			        usleep(milisegundos);
			        cout << "enviando mensaje : " << linea_final << endl;
					enviarMensajes(&this->datosConexion,idCliente,linea_final);
					cont++;

			   pos = (pos + tamanio)-tamanio_aux;
			   tamanio_aux = 0;
		   }
		       if ((pos == 0) && ((tamanio_aux+linea.length()) < tamanio)){
		    		   linea_aux = linea_aux + linea;
		    		   tamanio_aux = tamanio_aux + linea.length();
		       }else{
			         tamanio_aux = linea.length()- pos;
		             linea_aux = linea.substr(pos,tamanio_aux);
		       }
		       linea = " ";
        }
		file2.seekg(0);
		file2.close();

  }


	return 0;
}*/



int Cliente::getIpAndPort(){
	string inputIp;
	int inputPuerto;
	bool ok = false;

	cout << "Ingrese la ip del servidor ('l' para localhost):" << endl;
	cin >> inputIp;

	if (inputIp == "l"){
		strcpy(this->datosConexion.ip,"127.0.0.1");
	}else{
		strcpy(this->datosConexion.ip,inputIp.c_str());
	}

	cout << "Ingrese el puerto del servidor:" << endl;
	while (!ok){
		cin >> inputPuerto;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
			Log::log('s',3,"Puerto ingresado incorrecto","");
		}else{
			this->datosConexion.puerto = inputPuerto;
			ok = true;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return 0;
}


int Cliente::printMenu(){

	cout << endl;
	cout << "-----   MENÚ   -----------------------" << endl;
	cout << "1 - Conectar" << endl;
	cout << "2 - Desconectar" << endl;
	cout << "3 - Salir" << endl;
	cout << "---------------------------------------" << endl;

	return 0;
}
void Cliente::imprimirConsigna(){
	cout << endl;
	cout << "----- Seleccione una opción del menú: -------" << endl;
}

int Cliente::selectFromMenu(){
	int input;
	bool ok = false;
	int status;

	imprimirConsigna();
	while (!ok){
		cin >> input;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
			Log::log('c',3,"Menu: Numero ingresado incorrecto","");
		}else if(input<1 || input > 7){
			cout << "Error: Ingrese una de las opciones dadas" << endl;
			Log::log('c',3,"Menu: Opcion ingresada incorrecta","");
		}else
			ok = true;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	//--------------------------------------------

	switch (input){
		case 1:
			status = seleccConectar();
			break;
		case 2:
			status = seleccDesconectar();
			break;
		case 3:
			status = salir();
			break;
	/*	case 4:
			status = enviar();
			break;
		case 5:
			status = recibir();
			break;
		case 6:
			status = loremIpsum();
			break;
		case 7:
			status = getIpAndPort();
			break;*/
	}

	return status;


}


int Cliente::runCliente(){
	Log::log('c',1,"Starting client app","");
	cout << "Starting client app" << endl;

	int status = 0;
	this->threadRecv = 0;
	this->threadEscenario = 0;

	getIpAndPort();
	printMenu();

	while (status >= 0){
		status = selectFromMenu();
	}

	return 0;

};


string Cliente::getNombreUsuarioById(int idUsuario) {

	string nombre = "";

	map<int, string>::iterator it;

	if((it = this->mapIdNombreUsuario.find(idUsuario)) != this->mapIdNombreUsuario.end())
		nombre = this->mapIdNombreUsuario[idUsuario];

	return nombre;
}


list<int> Cliente::getIdUsuarios() {

	list<int> idUsuarios;
	map<int, string>::iterator it;

	for(it = this->mapIdNombreUsuario.begin(); it != this->mapIdNombreUsuario.end(); it++) {

		    idUsuarios.push_back(it->first);
	}

	return idUsuarios;
}
