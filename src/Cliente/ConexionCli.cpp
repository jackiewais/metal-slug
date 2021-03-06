#include "ConexionCli.h"
#include "../Common/Mensajeria.h"
#include "../Common/Log.h"
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
#include <vector>
#include <limits>

using namespace std;
int ConexionCli::desconectar(datosConexionStruct* datosConexion){
	mensajeStruct mensaje;
	mensaje.tipo = DISCONNECTED;
	mensaje.message = "Usuario desconectado";
	mensaje.objectId = "X0";

	encodeAndSend(datosConexion->sockfd, &mensaje);
	cerrarSocket(datosConexion->sockfd);

	return 0;
}

int ConexionCli::cerrarSocket(int socket){
	shutdown(socket, SHUT_RDWR);
	close(socket);
	printf("Usuario desconectado\n");
	Log::log('c',1,"Se cerro el socket","");
	return 0;
}

map<int, string> ConexionCli::conectar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	struct sockaddr_in their_addr;
	map<int, string> mapIdNombre;

	if ((datosConexion->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	//	perror("ERROR abriendo el socket");
		Log::log('c',3,"Abriendo el socket","");
		return mapIdNombre;
	}

	struct timeval timeout;
	 timeout.tv_sec = 60;

	 timeout.tv_usec = 60;

	 if (setsockopt (datosConexion->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		 Log::log('c',3,"Seteando el timeout para rcv","");
		// perror("ERROR seteando el timeout para rcv");

	 if (setsockopt (datosConexion->sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		 Log::log('c',3,"Seteando el timeout para snd","");
		// perror("ERROR seteando el timeout para snd");


	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(datosConexion->puerto);
	their_addr.sin_addr.s_addr = inet_addr(datosConexion->ip);
	memset(&(their_addr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (connect(datosConexion->sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
	//	perror("ERROR ejecutando connect");
		Log::log('c',3,"Ejecutando connect","");
		return mapIdNombre;
	} else {
		cout << "Conectado al servidor" << endl;
		Log::log('c',1,"Conectado al servidor","");
	}

	Mensajeria mensajeria;
	mensajeStruct rtaServer;
	mensajeria.receiveAndDecode(datosConexion->sockfd,&rtaServer);
	if (rtaServer.tipo == CONECTAR_NOTOK){
	//	printf("El servidor rechazó la conexión: Demasiados usuarios \n");
		Log::log('c',2,"El servidor rechazó la conexión: Demasiados usuarios","");
		printf("El servidor rechazó la conexión: Demasiados usuarios \n");
		return mapIdNombre;
	}
	return this->autenticar(datosConexion, usuario, contrasenia);
};


// Es necesario que se haya conectado mediante el socket previamente
// Devuelve el ID de usuario si pudo autenticar con exito, o -1 en caso de error
map<int, string> ConexionCli::autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	std::string usuarioYContrasenia = usuario + ";" + contrasenia;
	mensajeStruct mensaje;
	mensaje.message = usuarioYContrasenia;
	mensaje.objectId = "X0";
	mensaje.tipo = LOGIN;
	Mensajeria::encodeAndSend(datosConexion->sockfd, &mensaje);

	mensajeStruct mensajeRespuesta;
	Mensajeria::receiveAndDecode(datosConexion->sockfd,&mensajeRespuesta);

	map<int, string> mapIdNombre = this->getMapIdNombre(mensajeRespuesta.message);

	if (mensajeRespuesta.tipo == LOG_NOTOK) {
		printf("ERROR al momento de autenticar usuario y password ");
		Log::log('c',3,"Al momento de autenticar usuario y password ","");
	}else if(mapIdNombre.empty() && mensajeRespuesta.tipo == LOG_OK) {
		printf("No Hay Usuarios Disponibles \n");
		Log::log('c',2,"No Hay Usuarios Disponibles","");

	}
	return mapIdNombre;
}
int ConexionCli::enviarEvento(mensajeStruct *evento){


	return encodeAndSend(evento->socketCli,evento);

}

void ConexionCli::enviarMensajes(datosConexionStruct* datosConexion,int usuarioTo, string input){
	string buf;
	int pini=0;
	
	int lengthInput =  strlen(input.c_str());

	mensajeStruct mensaje;
	
	//mensaje.objectId = string(usuarioTo);
	mensaje.socketCli = datosConexion->sockfd;

	if (datosConexion->conectado){
		while(lengthInput>MAXDATASIZE){
		 	buf = input.substr(pini,MAXDATASIZE);
		 	pini+=MAXDATASIZE;
		 	lengthInput -= MAXDATASIZE;
		 	//ENVIAR MENSAJE SIGUIENTE
		 	mensaje.tipo = ENVIAR_CHAT_SIGUE;
		 	mensaje.message = buf;
		 	Mensajeria::encodeAndSend(datosConexion->sockfd, &mensaje);
		}
		if (lengthInput!=0){
			buf= input.substr(pini,lengthInput);
			//ENVIAR MENSAJE CON FIN
			mensaje.tipo = ENVIAR_CHAT_FIN;
			mensaje.message=buf;
			Mensajeria::encodeAndSend(datosConexion->sockfd, &mensaje);
		}
	}else{
		cout << "Usuario desconectado " << endl;
	}
}

int ConexionCli::recibirMensaje(datosConexionStruct* datosConexion, mensajeStruct* mensaje){
	return Mensajeria::receiveAndDecode(datosConexion->sockfd, mensaje);
}

int ConexionCli::pedirMensajes(datosConexionStruct* datosConexion){
	mensajeStruct mensaje;
	mensaje.tipo = RECIBIR_CHATS;
	mensaje.objectId = "X0";
	mensaje.message = "Quiero los chats";
	encodeAndSend(datosConexion->sockfd, &mensaje);
	return 0;
}

void ConexionCli::handshake(datosConexionStruct* datosConexion){
	cout << "pidiendo handshake" << endl;
	mensajeStruct mensaje;
	mensaje.tipo = RECIBIR_HANDSHAKE;
	mensaje.objectId = "X0";
	mensaje.message = "RECIBIR CONFIGURACION DEL MAPA";
	encodeAndSend(datosConexion->sockfd, &mensaje);
};

void split2(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> split2(const string &s, const char delim) {
    vector<string> elems;
    split2(s, delim, elems);
    return elems;
}


map<int, string> ConexionCli::getMapIdNombre(string idNombresUsuarios) {

	map<int, string> mapIdNombre;

	if((idNombresUsuarios != "Sin contenido") && (idNombresUsuarios != "")) {

		vector<string> vectorIdNombresUsuarios = split2(idNombresUsuarios, ';');
		vector<string> vectorUnElem;

		for(unsigned int i=0; i <= vectorIdNombresUsuarios.size()-1; i++) {

			string unIdNombreUsuario = vectorIdNombresUsuarios[i];
			vectorUnElem = split2(unIdNombreUsuario, '_');
			int idUsuario =  atoi(vectorUnElem[0].c_str());
			string nombre = vectorUnElem[1];

			mapIdNombre[idUsuario] = nombre;
		}
	}

	return mapIdNombre;
}


