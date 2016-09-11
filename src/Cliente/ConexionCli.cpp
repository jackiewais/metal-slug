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
	cerrarSocket(datosConexion->sockfd);
	printf("Usuario desconectado\n");

	return 0;
}

int ConexionCli::cerrarSocket(int socket){
	close(socket);
	return 0;
}

int ConexionCli::conectar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	struct sockaddr_in their_addr;
	int idUsuario = 5;

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
	their_addr.sin_addr.s_addr = inet_addr(datosConexion->ip);
	memset(&(their_addr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (connect(datosConexion->sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("ERROR ejecutando connect");
		return -1;
	} else {cout << "conectado al servidor" << endl;}

	Mensajeria mensajeria;
	mensajeStruct rtaServer;
	mensajeria.receiveAndDecode(datosConexion->sockfd,&rtaServer);
	if (rtaServer.tipo == CONECTAR_NOTOK){
		printf("El servidor rechazó la conexión: Demasiados usuarios \n");
		return -1;
	}

	idUsuario = autenticar(datosConexion, usuario, contrasenia);
	if ( idUsuario == -1 ) {
		perror("ERROR al momento de autenticar usuario y password");
		return -1;
	}


	return idUsuario;
};


// Es necesario que se haya conectado mediante el socket previamente
// Devuelve el ID de usuario si pudo autenticar con exito, o -1 en caso de error
int ConexionCli::autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	std::string usuarioYContrasenia = usuario + ";" + contrasenia;
	//Mensajeria mensajeria;

	mensajeStruct mensaje;
	mensaje.message = usuarioYContrasenia;
	mensaje.otherCli = 0;
	mensaje.tipo = LOGIN;
	Mensajeria::encodeAndSend(datosConexion->sockfd, &mensaje);

	mensajeStruct mensajeRespuesta;
	Mensajeria::receiveAndDecode(datosConexion->sockfd,&mensajeRespuesta);

	return 0; // Harcodeo para simular ID de usuario
}
void ConexionCli::enviarMensajes(datosConexionStruct* datosConexion){

	char message[30]="_ID.LONG.___MENSAJE___";
	send(datosConexion->sockfd, message , strlen(message) , 0);

}


