#ifndef CONEXIONCLI_H_
#define CONEXIONCLI_H_

#include <iostream>
#include <string.h>

class ConexionCli{

	public:
		struct datosConexionStruct{
			int sockfd;
			short puerto;
			char ip[16];
			bool conectado = false;
			int idUsuario = -1;
		};

		int conectar(datosConexionStruct* datosConexion);
		int autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia);
		int desconectar(datosConexionStruct* datosConexion);
};

#endif
