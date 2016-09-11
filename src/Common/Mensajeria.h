#ifndef MENSAJERIA_H_
#define MENSAJERIA_H_


#include <iostream>
#include <string>


class Mensajeria {

public:
	#define BUFLEN 1000

	enum tipoMensaje {
		LOG_OK = 01,
		LOG_NOTOK = 02,
		LOGIN = 03,
		CONECTAR_OK = 04,
		CONECTAR_NOTOK = 05,
		ENVIAR_CHAT_SIGUE = 11,
		ENVIAR_CHAT_FIN = 12,
		RECIBIR_CHATS = 13,
		DISCONNECTED = 99,

	};
	struct mensajeStruct {
		tipoMensaje tipo;
		int otherCli;
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
