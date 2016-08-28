#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Servidor {
private:
	int sockfd;
	struct sockaddr_in my_addr;
public:
	Servidor(short puerto);
	virtual ~Servidor();
	void escuchar(int conexiones_max);
};

#endif /* SERVIDOR_H_ */
