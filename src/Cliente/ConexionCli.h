#ifndef CONEXIONCLI_H_
#define CONEXIONCLI_H_

#include <iostream>
#include "../Common/Mensajeria.h"
#include <map>
#include <string>

using namespace std;

class ConexionCli:Mensajeria{

	public:
		struct datosConexionStruct{
			int sockfd;
			short puerto;
			char ip[16];
			bool conectado = false;
		};

		map<int, string> conectar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia);
		int desconectar(datosConexionStruct* datosConexion);
		void enviarMensajes(datosConexionStruct* datosConexion);
		int recibirMensaje(datosConexionStruct* datosConexion, mensajeStruct* mensaje);
		static void* recvMessage(void * arg);
		int cerrarSocket(int socket);
	private:
		map<int, string> autenticar(datosConexionStruct* datosConexion, std::string usuario, std::string contrasenia);
		map<int, string> getMapIdNombre(string idNombresUsuarios);
};

#endif
