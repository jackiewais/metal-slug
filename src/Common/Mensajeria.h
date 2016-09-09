#ifndef MENSAJERIA_H_
#define MENSAJERIA_H_


#include <iostream>
#include <string>

/*
 *  '01' = LOG_OK
 *  '02' = LOG_NOTOK
 *
 *
 *
 *
 *
 * */

class Mensajeria {

public:
	#define BUFLEN 1000

	struct mensajeStruct {
		char longit[3];
		char tipo[2];
		char otherCli[2];
		std::string message;
		int socketCli;
	};

	int encode(char output[BUFLEN], mensajeStruct* mensaje );
	int decode(char output[BUFLEN], mensajeStruct* mensaje);
	int encodeAndSend(int socketCli, mensajeStruct* mensaje);
	int receiveAndDecode(int socketCli, mensajeStruct* mensaje);

	bool insertarMensajeCola(int msgqid, mensajeStruct msg);
	bool crearCola(int &queue);
	bool extraerMensajeCola(int queue, mensajeStruct &msg);
};

#endif
