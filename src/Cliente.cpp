#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez

Cliente::Cliente() {
	if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}

void Cliente::conectar(char *ip, short puerto) {
	struct sockaddr_in their_addr;
	int numbytes;
	char buf[MAXDATASIZE];

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(puerto);
	//this->their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	their_addr.sin_addr.s_addr = inet_addr(ip);
	memset(&(their_addr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (connect(this->sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	if ((numbytes=recv(this->sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("Received: %s",buf);
}
