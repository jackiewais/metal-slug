#ifndef CONEXIONCLI_H_
#define CONEXIONCLI_H_


class ConexionCli{

	public:
		struct datosConexionStruct{
			int sockfd;
			short puerto;
			char ip[16];
			bool conectado = false;
		};

		int conectar(datosConexionStruct* datosConexion);
		int desconectar(datosConexionStruct* datosConexion);
		static void* recvMessage(void * arg);
};

#endif
