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
#include "./Modelo/EscenarioS.h"
#include "Contenedor.h"
#include "../Parser/Parser.h"


//#define XML_PATH "Parser/game.xml"

//using namespace std;


class Servidor:Mensajeria {
private:

	struct argsForThread{
		int* socketCli;
		Servidor* context;
	};

	const int MAX_CON = 6;
	int cantJugadores = 3;
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
	void handshake(mensajeStruct msg);
	int enviarMensajeSegmentado(int socketCli, chatStruct* elemento, queue<mensajeStruct>* colaCliente );
	Mensajeria mensajeria;
	Contenedor* contenedor;
	int procesarDesconexion(mensajeStruct mensaje);
	EscenarioS* escenario;

	bool cerrarPrograma;
	pthread_t threadExit, threadMain, threadTimer;
	int terminarThreads();
	void procesarTeclaPulsada(mensajeStruct msg);
	void createTimerThread();
	static void* manejarTimer (void *data);
	int idJugadores = 0;
	string convertirAString(int i);
	Parser *parser;
	string CSV_PATH = "usuarios.csv";
	string XML_PATH;



public:

	Servidor();
	virtual ~Servidor();
	void runServer();
};

#endif /* SERVIDOR_H_ */
