#include <sstream>
#include <string.h>
#include "Mensajeria.h"
#include <sys/socket.h>
#include <vector>

using namespace std;

int Mensajeria::encode(char output[BUFLEN], mensajeStruct* mensaje ){

	/*//Me devuelve el codigo de mensaje en 2 chars
	char codigo[2] = {0};
	snprintf(codigo, 2, "02%d", mensaje.tipo);*/

	strcpy(output,mensaje->longit);
	strcat(output,";");
	strcat(output,mensaje->tipo);
	strcat(output,";");
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

	vector<string> result = split(input, ';');
	string longitud = result[0];
	string tipo = result[1];
	strcpy(mensaje->longit, longitud.c_str());
	strcpy(mensaje->tipo, tipo.c_str());
	mensaje->message = result[2];

	return 0;
}

