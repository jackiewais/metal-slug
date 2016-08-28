#include "Servidor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

Servidor::Servidor(short puerto) {
	int yes=1;
	if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	if (setsockopt(this->sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	this->my_addr.sin_family = AF_INET;
	this->my_addr.sin_port = htons(puerto);
	this->my_addr.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
	memset(&(this->my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura
	if (bind(this->sockfd, (struct sockaddr *)&this->my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}
}

Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}

void sigchld_handler(int s) {
	while(wait(NULL) > 0);
}

void Servidor::escuchar(int conexiones_max) {
	socklen_t sin_size;
	struct sigaction sa;
	int new_fd;
	struct sockaddr_in their_addr; // información sobre la dirección del cliente

	if (listen(this->sockfd, conexiones_max) == -1) {
		perror("listen");
		exit(1);
	}
	sa.sa_handler = sigchld_handler; // Eliminar procesos muertos
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
	while(1) { // main accept() loop
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(this->sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n",
		inet_ntoa(their_addr.sin_addr));
		if (!fork()) { // Este es el proceso hijo
			close(this->sockfd); // El hijo no necesita este descriptor
			if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
				perror("send");
			close(new_fd);
			exit(0);
		}
		close(new_fd); // El proceso padre no lo necesita
	}
}
