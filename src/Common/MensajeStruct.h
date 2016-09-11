#ifndef MENSAJESTRUCT_H_
#define MENSAJESTRUCT_H_

#include <iostream>


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

#endif
