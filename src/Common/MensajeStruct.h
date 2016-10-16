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

	PULSA_TECLA=17,
	RECIBIR_HANDSHAKE=18,
	HANDSHAKE_DIMENSIONES_VENTANA=19,
	HANDSHAKE_SPRITES=20,
	HANDSHAKE_OBJETO_NUEVO=21,
	FIN_HANDSHAKE=22,
	JUGADOR_SO_VO=23,
	JUGADOR_NEW=25,
	JUGADOR_UPD=26,
	ESCENARIO_NEW=27,
	ESCENARIO_UPD=28,
	HANDSHAKE_FONDO_NUEVO = 29,
	HANDSHAKE_ESTADO_SPRITE=30,

	JUEGO_COMENZAR = 40
};


struct mensajeStruct {
	tipoMensaje tipo;
	std::string objectId;
	std::string message;
	int socketCli;
};

#endif
