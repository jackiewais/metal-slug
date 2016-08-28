#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Cliente {
private:
	struct sockaddr_in their_addr;

	struct datosConexionStruct{
		int sockfd;
		short puerto;
		char ip[16];
		bool conectado = false;
	};

	datosConexionStruct datosConexion;

	int conectar();
	int seleccConectar();
	int getIpAndPort();
	int selectFromMenu();

public:
	Cliente();
	virtual ~Cliente();
	int runCliente();
};

#endif /* CLIENTE_H_ */
