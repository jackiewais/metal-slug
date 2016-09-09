#include <sstream>
#include <string.h>
#include "Mensajeria.h"
#include <sys/socket.h>
#include <vector>
#include <sys/msg.h>
#include <sys/errno.h>

using namespace std;

int Mensajeria::encode(char output[BUFLEN], mensajeStruct* mensaje ){

	strcpy(output,mensaje->longit);
	strcat(output,"#");
	strcat(output,mensaje->tipo);
	strcat(output,"#");
	strcat(output,mensaje->otherCli);
	strcat(output,"#");
	strcat(output,mensaje->message.c_str());

	return 0;
}


int Mensajeria::encodeAndSend(int socketCli, mensajeStruct* mensaje){
	char output[BUFLEN];

	encode(output,mensaje);
	int n = send(socketCli,output,atoi(mensaje->longit),0);
	if (n < 0) {
		printf("ERROR enviando mensaje");
		return 1;
	}

	return 0;
}


void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


int Mensajeria::decode(char input[BUFLEN], mensajeStruct* mensaje){

	vector<string> result = split(input, '#');
	string longitud = result[0];
	string tipo = result[1];
	strcpy(mensaje->longit, longitud.c_str());
	strcpy(mensaje->tipo, tipo.c_str());
	mensaje->message = result[2];

	return 0;
}


int Mensajeria::receiveAndDecode(int socketCli, mensajeStruct* mensaje){

	 int n;
	 char buffer[BUFLEN];
	 int error = 0;

	bzero(buffer,BUFLEN);
	n = recv(socketCli, buffer, BUFLEN-1, 0);
	if (n < 0) {
		printf("ERROR ejecutano recv");
		strcpy(mensaje->longit,"000");
		strcpy(mensaje->tipo,"99");
		mensaje->message = "Error leyendo del socket";
		error = 1;
	}else if (n == 0){
		printf("Mensaje de salida recibido");
		strcpy(mensaje->longit,"000");
		strcpy(mensaje->tipo,"99");
		mensaje->message = "Usuario desconectado";
		error = 1;
	}else{
		decode(buffer,mensaje);
		error = 0;
	}

	mensaje->socketCli = socketCli;

	return error;
}



bool Mensajeria::insertarMensajeCola(int msgqid, mensajeStruct msg){
	int rc;

	rc = msgsnd(msgqid, &msg, sizeof(mensajeStruct), 0);
	if (rc < 0) {
		perror(strerror(errno));
		printf("ERROR: agregando mensaje a la cola.\n");
		return false;
	}

	return true;
}

bool Mensajeria::crearCola(int &queue){

	queue = msgget(IPC_PRIVATE, 0666|IPC_CREAT|IPC_EXCL);
	if (queue < 0) {
	  perror(strerror(errno));
	  printf("ERROR: creando cola de mensajes.\n");
	  return false;
	}
	return true;
}

bool Mensajeria::extraerMensajeCola(int queue, mensajeStruct &msg){
	int rc;

	rc = msgrcv(queue, &msg, sizeof(mensajeStruct), 0, 0);
	if (rc < 0) {
		perror( strerror(errno) );
		printf("ERROR: sacando mensaje de la cola.\n");
		return false;
	}

	return true;
}
