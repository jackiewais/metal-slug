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

	return 0;
};

// Es necesario que se haya conectado mediante el socket previamente
// Devuelve el ID de usuario si pudo autenticar con exito, o -1 en caso de error
int ConexionCli::autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	std::string usuarioYContrasenia = usuario + ";" + contrasenia;

	if (send(datosConexion->sockfd, usuarioYContrasenia.c_str(), strlen(usuarioYContrasenia.c_str()), 0) == -1)
		perror("ERROR ejecutando send");

	// ACA HAY QUE ESPERAR RESPUESTA DEL SERVIDOR Y EN BASE A ESO
	// RETORNAR ID DE USUARIO(TENDRIA QUE MANDARLA EL SERVER) O -1

	return 502; // Harcodeo para simular ID de usuario
}
