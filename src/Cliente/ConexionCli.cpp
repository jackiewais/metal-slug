#include "ConexionCli.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez

int ConexionCli::desconectar(datosConexionStruct* datosConexion){
	char message[256];
	memset(message,0,256);
	message[0]= 'q';

	send(datosConexion->sockfd, message , strlen(message) , 0);
	close(datosConexion->sockfd);
	printf("Usuario desconectado");

	return 0;
}


int ConexionCli::conectar(datosConexionStruct* datosConexion) {
	struct sockaddr_in their_addr;
	int numbytes;
	char buf[MAXDATASIZE];

	if ((datosConexion->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR abriendo el socket");
		return 1;
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
		return 1;
	}
	printf("Usuario conectado");
	if ((numbytes=recv(datosConexion->sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("ERROR ejecutando recv");
		return 1;
	}
	buf[numbytes] = '\0';
	printf("Received: %s",buf);

	return 0;
};
