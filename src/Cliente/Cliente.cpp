#include "Cliente.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <string.h>

using namespace std;

#define MAXDATASIZE 100 // máximo número de bytes que se pueden leer de una vez

Cliente::Cliente() {

}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}


int Cliente::seleccConectar(){
	int respuesta = 1, idUsuario;
	string usuario, contrasenia;

	if (this->datosConexion.conectado){
		cout << "El usuario ya está conectado" << endl;
		respuesta = 0;
	}else{
		getUsuarioYContrasenia(usuario, contrasenia);
		idUsuario = conectar(&this->datosConexion, usuario, contrasenia);
		if (idUsuario > 0){
			this->datosConexion.idUsuario = idUsuario;
			this->datosConexion.conectado = true;
			respuesta = 0;
		}

	}

	return respuesta;
}

int Cliente::getUsuarioYContrasenia(string &usuario, string &contrasenia){
	string inputUsuario, inputContrasenia;
	bool ok = false;

	while (!ok){
		cout << "Ingrese el nombre de usuario:" << endl;
		cin >> usuario;
		if (usuario.find(";") == string::npos)
			ok = true;
	}

	ok = false;
	while (!ok){
		cout << "Ingrese la contraseña:" << endl;
		cin >> contrasenia;
		if (contrasenia.find(";") == string::npos)
			ok = true;
	}

	return 0;
}

int Cliente::seleccDesconectar(){
	int respuesta = 0;

	if (!this->datosConexion.conectado){
		cout << "El usuario no está conectado" << endl;
	}else{
		respuesta = desconectar(&this->datosConexion);
		if (respuesta == 0)
			this->datosConexion.conectado = false;
	}

	return respuesta;
}

int Cliente::salir(){
	seleccDesconectar();
	return -1;
}

int Cliente::enviar(){

	return 0;
}

int Cliente::recibir(){

	return 0;
}

int Cliente::loremIpsum(){

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
			status = seleccDesconectar();
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