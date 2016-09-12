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
#include <vector>
#include <limits>

using namespace std;
int ConexionCli::desconectar(datosConexionStruct* datosConexion){
	mensajeStruct mensaje;
	mensaje.tipo = DISCONNECTED;
	mensaje.message = "Usuario desconectado";
	mensaje.otherCli = 0;

	encodeAndSend(datosConexion->sockfd, &mensaje);
	cerrarSocket(datosConexion->sockfd);

	return 0;
}

int ConexionCli::cerrarSocket(int socket){
	close(socket);
	printf("Usuario desconectado\n");
	return 0;
}

map<int, string> ConexionCli::conectar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	struct sockaddr_in their_addr;
	map<int, string> mapIdNombre;

	if ((datosConexion->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR abriendo el socket");
		return mapIdNombre;
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
		return mapIdNombre;
	} else {cout << "conectado al servidor" << endl;}

	Mensajeria mensajeria;
	mensajeStruct rtaServer;
	mensajeria.receiveAndDecode(datosConexion->sockfd,&rtaServer);
	if (rtaServer.tipo == CONECTAR_NOTOK){
		printf("El servidor rechazó la conexión: Demasiados usuarios \n");
		return mapIdNombre;
	}

	mapIdNombre = this->autenticar(datosConexion, usuario, contrasenia);

	if (mapIdNombre.empty()) {
			perror("ERROR al momento de autenticar usuario y password");
			return mapIdNombre;
	}
	return mapIdNombre;
};


// Es necesario que se haya conectado mediante el socket previamente
// Devuelve el ID de usuario si pudo autenticar con exito, o -1 en caso de error
map<int, string> ConexionCli::autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia) {
	std::string usuarioYContrasenia = usuario + ";" + contrasenia;
	//Mensajeria mensajeria;

	mensajeStruct mensaje;
	mensaje.message = usuarioYContrasenia;
	mensaje.otherCli = 0;
	mensaje.tipo = LOGIN;
	Mensajeria::encodeAndSend(datosConexion->sockfd, &mensaje);

	mensajeStruct mensajeRespuesta;
	Mensajeria::receiveAndDecode(datosConexion->sockfd,&mensajeRespuesta);

	std::cout << mensajeRespuesta.message << endl;

	return this->getMapIdNombre(mensajeRespuesta.message);
}
void ConexionCli::enviarMensajes(datosConexionStruct* datosConexion){
	string input;
	string buf;
	cout << "INRESE MENSAJE A ENVIAR "<< endl;
	getline (cin,input);
	int lengthInput =  strlen(input.c_str());//input.length();
	int pini=0;
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	mensajeStruct mensaje;
	
	mensaje.otherCli = 2;
	
	mensaje.socketCli = datosConexion->sockfd;

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
}

int ConexionCli::recibirMensaje(datosConexionStruct* datosConexion, mensajeStruct* mensaje){
	return Mensajeria::receiveAndDecode(datosConexion->sockfd, mensaje);
}

int ConexionCli::pedirMensajes(datosConexionStruct* datosConexion){
	mensajeStruct mensaje;
	mensaje.tipo = RECIBIR_CHATS;
	mensaje.otherCli = 0;
	mensaje.message = "Quiero los chats";
	encodeAndSend(datosConexion->sockfd, &mensaje);
	return 0;
}

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

	if(idNombresUsuarios != "") {

		vector<string> vectorIdNombresUsuarios = split2(idNombresUsuarios, ';');
		vector<string> vectorUnElem;

		for(unsigned int i=0; i < vectorIdNombresUsuarios.size()-1; i++) {

			string unIdNombreUsuario = vectorIdNombresUsuarios[i];
			vectorUnElem = split2(unIdNombreUsuario, '_');
			int idUsuario =  atoi(vectorUnElem[0].c_str());
			string nombre = vectorUnElem[1];

			mapIdNombre[idUsuario] = nombre;
		}
	}

	return mapIdNombre;
}


