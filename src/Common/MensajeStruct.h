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
	RECIBIR_CHAT_SIGUE = 14,
	RECIBIR_CHAT_FIN = 15,
	RECIBIR_CHATS_LISTO = 16,
	DISCONNECTED = 99,
	RECIBIR_HANDSHAKE = 98,
	FIN_HANDSHAKE=97,

};

struct mensajeStruct {
	tipoMensaje tipo;
	std::string objectId;
	std::string message;
	int socketCli;
};

#endif
