#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
#include "../Common/ChatStruct.h"
#include "../Common/Mensajeria.h"
#include <queue>
#include "ContenedorUsuarios.h"

//using namespace std;


class Servidor:Mensajeria {
private:

	struct argsForThread{
		int* socketCli;
		Servidor* context;
	};

	const int MAX_CON = 6;
	std::queue<mensajeStruct> colaPrincipalMensajes;
	std::map<int,queue<mensajeStruct>*> socketIdQueue;
	int sockfd = 0;
	int cantCon = 0;
	struct sockaddr_in my_addr;
	std::multimap<int,chatStruct> waitingChats;
	int colaPrincipal=0;
	argsForThread* arguments;

	int openSocket(short puerto);
	int escuchar();

	void createExitThread();
	static void* exitManager(void* data);
	void cerarSockets();
	void nuevaConexion(int new_fd);
	static void* recibirMensajesCliente(void* arguments);
	static void* sendMessage(void*arguments);
	void createMainProcessorThread();
	static void* procesarMensajesMain (void *data) ;
	int procesarMensajeCola(mensajeStruct msg);
	int loginInterpretarMensaje(mensajeStruct msg);
	int enviarChat(mensajeStruct msg);
	int recibirTodosLosChats(mensajeStruct msg);
	int enviarMensajeSegmentado(int socketCli, chatStruct* elemento, queue<mensajeStruct>* colaCliente );
	Mensajeria mensajeria;
	ContenedorUsuarios* contenedor;
	int procesarDesconexion(mensajeStruct mensaje);

	bool cerrarPrograma;
	pthread_t threadExit, threadMain;
	int terminarThreads();

public:
	Servidor();
	virtual ~Servidor();
	void runServer();
};

#endif /* SERVIDOR_H_ */
