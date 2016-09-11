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
	const int MAX_CON = 6;

	int sockfd = 0;
	int cantCon = 0;
	struct sockaddr_in my_addr;
	std::multimap<int,chatStruct> waitingChats;
	int colaPrincipal=0;

	int openSocket(short puerto);
	int escuchar();

	void createExitThread();
	static void* exitManager(void* data);
	void cerarSockets();
	void nuevaConexion(int new_fd);
	static void* recibirMensajesCliente(void* socketCli);
	void createMainProcessorThread();
	static void* procesarMensajesMain (void *data) ;
	int procesarMensajeCola(mensajeStruct msg);
	int loginInterpretarMensaje(mensajeStruct msg);

	Mensajeria* mensajeria;

public:
	Servidor();
	virtual ~Servidor();
	void runServer();
};

#endif /* SERVIDOR_H_ */
