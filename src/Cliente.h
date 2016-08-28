#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Cliente {
private:
	int sockfd;
	struct sockaddr_in their_addr;
public:
	Cliente(short puerto);
	virtual ~Cliente();
	void conectar();
};

#endif /* CLIENTE_H_ */
