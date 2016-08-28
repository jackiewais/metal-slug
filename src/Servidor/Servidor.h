#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Servidor {
private:
	int sockfd = 0;
	struct sockaddr_in my_addr;

	int openSocket(short puerto);
	int escuchar();

public:
	Servidor();
	virtual ~Servidor();
	void runServer();
};

#endif /* SERVIDOR_H_ */
