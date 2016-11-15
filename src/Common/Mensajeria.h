#ifndef MENSAJERIA_H_
#define MENSAJERIA_H_

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "MensajeStruct.h"
#include "Util.h"

class Mensajeria {

public:
	#define BUFLEN 62
	#define MAXDATASIZE 50 // máximo número de bytes que se pueden leer de una vez

	int encode(char output[BUFLEN], mensajeStruct* mensaje );
	int decode(char output[BUFLEN], mensajeStruct* mensaje);
	int encodeAndSend(int socketCli, mensajeStruct* mensaje);
	int receiveAndDecode(int socketCli, mensajeStruct* mensaje);

	bool insertarMensajeCola(int msgqid, mensajeStruct *msg);
	bool crearCola(int &queue);
	bool extraerMensajeCola(int queue, mensajeStruct &msg);


};

#endif
