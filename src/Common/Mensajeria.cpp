#include <sstream>
#include "Log.h"
#include <string.h>
#include "Mensajeria.h"
#include <sys/socket.h>
#include <vector>
#include <sys/msg.h>
#include <sys/errno.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
   
    

int Mensajeria::encode(char output[BUFLEN], mensajeStruct* mensaje ){

	char tipo[3], longit[4];
	int tipoI = mensaje->tipo;
	snprintf(tipo, 3, "%02d", tipoI);

	int longitudI = strlen(mensaje->message.c_str()) + strlen(mensaje->objectId.c_str()) + 2 + 3 + 4; //mensaje + objectId + tipo + separadores + longit
	snprintf(longit, 5, "%04d", longitudI);
	int resto = (BUFLEN-1)-longitudI;

	strcpy(output,longit);
	strcat(output,"|");
	strcat(output,tipo);
	strcat(output,"|");
	strcat(output,mensaje->objectId.c_str());
	strcat(output,"|");
	strcat(output,mensaje->message.c_str());
	if (longitudI<BUFLEN-1){
		strcat(output,"|");
		strcat(output,string(resto-1, '1').c_str());
	}
	return 0;
}


int Mensajeria::encodeAndSend(int socketCli, mensajeStruct* mensaje){

	char output[BUFLEN];
	bzero(output,BUFLEN);
	int longit = encode(output,mensaje);

	//cout << "\n Mensaje enviandose: " << output << endl;
	//cout << "LEN: " << strlen(output) << endl;

	int n = send(socketCli,output,strlen(output),0);
	if (n < 0) {
		//	perror("ERROR enviando mensaje");
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


vector<string> split(const string &s, const char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


int Mensajeria::decode(char input[BUFLEN], mensajeStruct* mensaje){

	vector<string> result = split(input, '|');
	string longitud = result[0];
	string tipoS = result[1];
	int tipo = atoi(tipoS.c_str());
	string objectIdS = result[2];
	int objectId = atoi(objectIdS.c_str());

	mensaje->tipo = static_cast<tipoMensaje>(tipo);
	mensaje->objectId = objectId;
	if (result.size() < 4){
		mensaje->message = "Sin contenido";
	}else{
		mensaje->message = result[3];
	}

	return 0;
}


int Mensajeria::receiveAndDecode(int socketCli, mensajeStruct* mensaje){
	 int n;
	 char buffer[BUFLEN];
	 int error = 0;

	bzero(buffer,BUFLEN);
	n = recv(socketCli, buffer, BUFLEN-1, 0);
	if (n < 0) {
	//	perror("ERROR ejecutano recv \n");
		mensaje->tipo = DISCONNECTED;
		mensaje->message = "Error leyendo del socket";
		mensaje->objectId = "0";
		error = 1;
	}else if (n == 0){
		//printf("Mensaje de salida recibido \n");
		mensaje->tipo = DISCONNECTED;
		mensaje->message = "Usuario desconectado";
		mensaje->objectId = "0";
		error = 1;
	}else{
	//	cout << "\n Mensaje recibido: " << buffer << endl;
		decode(buffer,mensaje);
		error = 0;
	}

	mensaje->socketCli = socketCli;
	return error;
}



bool Mensajeria::insertarMensajeCola(int msgqid, mensajeStruct *msg){
	/*int rc;

	rc = msgsnd(msgqid, &msg, sizeof(mensajeStruct), 0);
	if (rc < 0) {
		perror(strerror(errno));
		printf("ERROR: agregando mensaje a la cola.\n");
		return false;
	}*/
	//colaPrincipalMensajes.push(msg);
	
	return true;
}

bool Mensajeria::crearCola(int &queue){
	queue = msgget(IPC_PRIVATE, 0666|IPC_CREAT|IPC_EXCL);
	if (queue < 0) {
	  perror(strerror(errno));
	//  printf("ERROR: creando cola de mensajes.\n");
	  return false;
	}
	return true;
}

bool Mensajeria::extraerMensajeCola(int queue, mensajeStruct &msg){
	int rc;

	rc = msgrcv(queue, &msg, sizeof(mensajeStruct), 0, 0);
	if (rc < 0) {
		perror( strerror(errno) );
	//	printf("ERROR: sacando mensaje de la cola.\n");
		return false;
	}

	return true;
}
