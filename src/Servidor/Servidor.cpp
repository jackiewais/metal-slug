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

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez




void* Servidor::procesarMensajesMain (void *data) {
	mensajeStruct msg;
	Servidor* context = (Servidor*)data;
	bool finish = false;
	int result;

	if (!context->mensajeria->crearCola(context->colaPrincipal)) {
		finish = true;
	}

	while(!finish){
		if (!context->mensajeria->extraerMensajeCola(context->colaPrincipal, msg)) {
			finish = true;
		}else{
			printf("Procesando Mensaje: %s",msg.message.c_str());
			result = context->procesarMensajeCola(msg);
			finish = (result != 0);
		}
	}

	return 0;

}

int Servidor::procesarMensajeCola(mensajeStruct msg){
	//EN FUNCIÓN AL TIPO DE MSJ VER QUE SE HACE

	//Writes the message in the socket's queue
	//	writeQueueMessage(msg.msocket,response, msg.minfo, true);

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
	struct argsForThread* args = (argsForThread*) arguments;
	int socketCli = *(args->socketCli);
	bool finish = false;

   int n;
   char buffer[BUFLEN];
   mensajeStruct mensaje;

   //Receive a message from client
   while(!finish){
	   mensaje = {}; //Reset struct
		bzero(buffer,BUFLEN);
		n = recv(socketCli, buffer, BUFLEN-1, 0);
		if (n < 0) {
			printf("ERROR ejecutano recv");
			strcpy(mensaje.longit,"000");
			strcpy(mensaje.tipo,"99");
			mensaje.message = "Error leyendo del socket";
			finish = true;
		}else if (n == 0){
			printf("Mensaje de salida recibido");
			strcpy(mensaje.longit,"000");
			strcpy(mensaje.tipo,"99");
			mensaje.message = "Usuario desconectado";
			finish = true;
		}else{
			args->context->mensajeria->decode(buffer,&mensaje);
		}

		mensaje.socketCli = socketCli;

		//
   }

   close(socketCli);

	return 0;
}


void sigchld_handler(int s) {
	while(wait(NULL) > 0);
}

void *sendMessage(void *nw_fd){
	
	int new_fd = *(int *)nw_fd;
	char buf[20] = "Recibido.Cambio";
	send(new_fd, buf , 20, 0);
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

	char buf[MAXDATASIZE];
	char *usuario, *contrasenia;
	int numbytes;
	char * pch;
	struct timeval timeout;
	//int new_fd = *(int *)nw_fd;
	timeout.tv_sec = 60;
	timeout.tv_usec = 0;
	pthread_t precvMessage;
	pthread_t psendMessage;
	

	if (setsockopt (new_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		printf("ERROR setealdo el rcv timeout \n");
	if (setsockopt (new_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		printf("ERROR setealdo el snd timeout \n");

	int cola_socket;
	mensajeria->crearCola(cola_socket); //TODO: AGREGAR ESTO A LOS DATOS DEL USER

/*	if ((numbytes=recv(new_fd, (void*)&buf, MAXDATASIZE-1, 0)) == -1) {
		perror("ERROR ejecutando recv");
	}

	buf[numbytes] = '\0';
	pch = strtok( buf, ";" );
	usuario = pch;
	pch = strtok( NULL, ";" );
	contrasenia = pch;

	cout << new_fd << endl;
	printf("%s, %s\n", usuario, contrasenia);*/
	
	int rc = pthread_create(&precvMessage, NULL, recibirMensajesCliente, (void*)&new_fd);
	if (rc){
		printf("ERROR creando el thread de recv %i \n",rc);
	}
	
	rc = pthread_create(&precvMessage, NULL, sendMessage, (void*)&new_fd);
	if (rc){
		printf("ERROR creando el thread de send %i \n",rc);
	}



	// ACA HAY QUE CHECKEAR EL USUARIO Y LA CONTRASENIA
	// SI SE PUDO LOGUEAR, HAY QUE DEVOLVERLE OK AL CLIENTE
	// Y ADEMAS LANZAR UN THREAD PARA RECV Y OTRO PARA SEND
	// SE PODRIA LANZAR SOLAMENTE UNO Y PARA EL OTRO APROVECHAR ESTE THREAD

	//close(new_fd);

	
}

int Servidor::escuchar() {
	socklen_t sin_size;
	//struct sigaction sa;
	int new_fd;
	struct sockaddr_in their_addr; // información sobre la dirección del cliente
	pthread_t thread;

	while(1) { // main accept() loop
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(this->sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("ERROR ejecutando accept \n");
			continue;
		}
		cout << "NUEVA CONEXION:";
		
		printf(" got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		cout << "==============" << endl;
		nuevaConexion(new_fd);

		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));


		 close(new_fd);

		/*if (!fork()) { // Este es el proceso hijo
			close(this->sockfd); // El hijo no necesita este descriptor
			if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
				perror("send");
			close(new_fd);
			exit(0);
		}
		close(new_fd); // El proceso padre no lo necesita*/

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
	mensajeria = new Mensajeria();
}
Servidor::~Servidor() {
	delete mensajeria;
}
