#include "ConexionCli.h"
#include "../Common/Mensajeria.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez

using namespace std;
int ConexionCli::desconectar(datosConexionStruct* datosConexion){
	char message[256];
	memset(message,0,256);
	message[0]= 'q';

	send(datosConexion->sockfd, message , strlen(message) , 0);
	close(datosConexion->sockfd);
	printf("Usuario desconectado\n");

	return 0;
}


int ConexionCli::conectar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	struct sockaddr_in their_addr;
	int idUsuario;

	if ((datosConexion->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR abriendo el socket");
		return -1;
	}

	struct timeval timeout;
	 timeout.tv_sec = 180;
	 timeout.tv_usec = 0;

	 if (setsockopt (datosConexion->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		 perror("ERROR seteando el timeout para rcv");

	 if (setsockopt (datosConexion->sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		 perror("ERROR seteando el timeout para snd");


	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(datosConexion->puerto);
	//this->their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	their_addr.sin_addr.s_addr = inet_addr(datosConexion->ip);
	memset(&(their_addr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (connect(datosConexion->sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("ERROR ejecutando connect");
		return -1;
	}

	idUsuario = autenticar(datosConexion, usuario, contrasenia);
	if ( idUsuario == -1 ) {
		perror("ERROR al momento de autenticar usuario y password");
		return -1;
	}

	printf("Usuario conectado con ID: %d\n", idUsuario);

	//CREO HILO PARA ESCUCHAR
	pthread_t threadRecv;

	int rc = pthread_create(&threadRecv, NULL,&ConexionCli::recvMessage,(void*)datosConexion);
	if (rc){
		printf("ERROR creando el thread  %i \n",rc);
	}

	return idUsuario;
};

void *ConexionCli::recvMessage(void * arg){

	int numbytes;
	char buf[MAXDATASIZE];

	datosConexionStruct* conexion = (datosConexionStruct*)arg;

	if ((numbytes=recv(conexion->sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("ERROR ejecutando recv");
		
	}
	buf[numbytes] = '\0';
	printf("Received: %s",buf);

};

// Es necesario que se haya conectado mediante el socket previamente
// Devuelve el ID de usuario si pudo autenticar con exito, o -1 en caso de error
int ConexionCli::autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	std::string usuarioYContrasenia = usuario + ";" + contrasenia;

	if (send(datosConexion->sockfd, usuarioYContrasenia.c_str(), strlen(usuarioYContrasenia.c_str()), 0) == -1) {
		perror("ERROR ejecutando send");
		return -1;
	}

	// ACA HAY QUE ESPERAR RESPUESTA DEL SERVIDOR Y EN BASE A ESO
	// RETORNAR ID DE USUARIO(TENDRIA QUE MANDARLA EL SERVER) O -1

	return 502; // Harcodeo para simular ID de usuario
}
