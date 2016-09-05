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

using namespace std;

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez

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

Servidor::Servidor() {

}
Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}

void sigchld_handler(int s) {
	while(wait(NULL) > 0);
}

void *nuevaConexion(void *nw_fd) {
	char buf[MAXDATASIZE];
	char *usuario, *contrasenia;
	int numbytes;
	char * pch;
	struct timeval timeout;
	int new_fd = *(int *)nw_fd;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	if (setsockopt (new_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		printf("ERROR setealdo el rcv timeout \n");
	if (setsockopt (new_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		printf("ERROR setealdo el snd timeout \n");


	if ((numbytes=recv(new_fd, (void*)&buf, MAXDATASIZE-1, 0)) == -1) {
		perror("ERROR ejecutando recv");
	}

	buf[numbytes] = '\0';
	pch = strtok( buf, ";" );
	usuario = pch;
	pch = strtok( NULL, ";" );
	contrasenia = pch;

	cout << new_fd << endl;
	printf("%s, %s\n", usuario, contrasenia);

	// ACA HAY QUE CHECKEAR EL USUARIO Y LA CONTRASENIA
	// SI SE PUDO LOGUEAR, HAY QUE DEVOLVERLE OK AL CLIENTE
	// Y ADEMAS LANZAR UN THREAD PARA RECV Y OTRO PARA SEND
	// SE PODRIA LANZAR SOLAMENTE UNO Y PARA EL OTRO APROVECHAR ESTE THREAD

	close(new_fd);

	return 0;
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
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

		pthread_create(&thread, NULL, nuevaConexion, (void*)&new_fd);
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
