#ifndef CONEXIONCLI_H_
#define CONEXIONCLI_H_

#include <iostream>
#include <string.h>
#include "../Common/Mensajeria.h"

class ConexionCli:Mensajeria{

	public:
		struct datosConexionStruct{
			int sockfd;
			short puerto;
			char ip[16];
			bool conectado = false;
			int idUsuario = -1;
		};

		int conectar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia);
		int desconectar(datosConexionStruct* datosConexion);
		void enviarMensajes(datosConexionStruct* datosConexion);
		static void* recvMessage(void * arg);
	private:
		int autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia);
};

#endif
