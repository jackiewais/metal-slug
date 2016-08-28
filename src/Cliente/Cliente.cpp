#include "Cliente.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez

Cliente::Cliente() {

}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}

int Cliente::conectar() {
	struct sockaddr_in their_addr;
	int numbytes;
	char buf[MAXDATASIZE];

	if ((this->datosConexion.sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR abriendo el socket");
		return 1;
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(datosConexion.puerto);
	//this->their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	their_addr.sin_addr.s_addr = inet_addr(datosConexion.ip);
	memset(&(their_addr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (connect(this->datosConexion.sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("ERROR ejecutando connect");
		return 1;
	}
	if ((numbytes=recv(this->datosConexion.sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("ERROR ejecutando recv");
		return 1;
	}
	buf[numbytes] = '\0';
	printf("Received: %s",buf);

	this->datosConexion.conectado = true;
	return 0;
}



int Cliente::seleccConectar(){
	int respuesta = 0;

	if (this->datosConexion.conectado){
		cout << "El usuario ya está conectado" << endl;
	}else{
		respuesta = conectar();
	}

	return respuesta;
}

int desconectar(){

	return 0;
}

int salir(){

	return -1;
}

int enviar(){

	return 0;
}

int recibir(){

	return 0;
}

int loremIpsum(){

	return 0;
}


int Cliente::getIpAndPort(){
	string inputIp;
	int inputPuerto;
	bool ok = false;

	cout << "Ingrese la ip del servidor ('l' para localhost):" << endl;
	cin >> inputIp;

	if (inputIp == "l"){
		strcpy(this->datosConexion.ip,"127.0.0.1");
	}else{
		strcpy(this->datosConexion.ip,inputIp.c_str());
	}

	cout << "Ingrese el puerto del servidor:" << endl;
	while (!ok){
		cin >> inputPuerto;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
		}else{
			this->datosConexion.puerto = inputPuerto;
			ok = true;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return 0;
}


int printMenu(){

	cout << "-----   MENÚ   -----------------------" << endl;
	cout << "1 - Conectar" << endl;
	cout << "2 - Desconectar" << endl;
	cout << "3 - Salir" << endl;
	cout << "4 - Enviar" << endl;
	cout << "5 - Recibir" << endl;
	cout << "6 - Lorem Ipsum" << endl;
	cout << "7 - Reingresar ip y puerto" << endl;
	cout << "---------------------------------------" << endl;

	return 0;
}

int Cliente::selectFromMenu(){
	int input;
	bool ok = false;
	int status;

	cout << "---------------" << endl;
	cout << "Seleccione una opción del menú:" << endl;

	while (!ok){
		cin >> input;
		if (!cin){ //Validates if its a number
			cout << "Error: Debe ingresar un número" << endl;
		}else if(input<1 || input > 6){
			cout << "Error: Ingrese una de las opciones dadas" << endl;
		}else
			ok = true;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	//--------------------------------------------

	switch (input){
		case 1:
			status = seleccConectar();
			break;
		case 2:
			status = desconectar();
			break;
		case 3:
			status = salir();
			break;
		case 4:
			status = enviar();
			break;
		case 5:
			status = recibir();
			break;
		case 6:
			status = loremIpsum();
			break;
		case 7:
			status = getIpAndPort();
			break;
	}

	return status;


}
int Cliente::runCliente(){
	cout << "Starting client app" << endl;

	int status = 0;

	getIpAndPort();
	printMenu();

	while (status >= 0){
		status = selectFromMenu();
	}

	return 0;

};
