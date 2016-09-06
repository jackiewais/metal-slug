#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
#include "../Common/ChatStruct.h"
#include "../Common/Mensajeria.h"

class Servidor:Mensajeria {
private:
	int sockfd = 0;
	struct sockaddr_in my_addr;
	std::multimap<int,chatStruct> waitingChats;

	int openSocket(short puerto);
	int escuchar();

	void createExitThread();
	static void* exitManager(void* data);
	void cerarSockets();
	void nuevaConexion(int new_fd);
	//void manejarNuevaConexion(int socketCli);
	static void* recibirMensajesCliente(void* socketCli);

	Mensajeria* mensajeria;

public:
	Servidor();
	virtual ~Servidor();
	void runServer();
};

#endif /* SERVIDOR_H_ */
