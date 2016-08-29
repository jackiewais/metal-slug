#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Cliente {
private:
	int sockfd;
public:
	Cliente();
	virtual ~Cliente();
	void conectar(char *ip, short puerto);
};

#endif /* CLIENTE_H_ */
