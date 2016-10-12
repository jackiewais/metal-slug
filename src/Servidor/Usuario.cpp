#include "Usuario.h"
#include <string>
#include <stdio.h>

using namespace std;

Usuario::Usuario(int idUsuario, string nombre, string pass) {
	this->idUsuario = idUsuario;
	this->idSocket = 0;
	this->nombre = nombre;
	this->pass = pass;
	this->conectado = false;
	this->idJugador = 0;
}

Usuario::~Usuario() {
	// TODO Auto-generated destructor stub
}


int  Usuario::getIdUsuario() {
	return this->idUsuario;
}


void Usuario::setIdUsuario(int idUsuario) {
	this->idUsuario = idUsuario;
}


int  Usuario::getIdJugador() {
	return this->idJugador;
}


void Usuario::setIdJugador(int idJugador) {
	this->idJugador = idJugador;
}


int  Usuario::getIdSocket() {
	return this->idSocket;
}


void Usuario::setIdSocket(int idSocket) {
	this->idSocket = idSocket;
}


string  Usuario::getNombre() {
	return this->nombre;
}


void Usuario::setNombre(string nombre) {
	this->nombre = nombre;
}


string  Usuario::getPass() {
	return this->pass;
}


void Usuario::setPass(string pass) {
	this->pass = pass;
}


bool Usuario::isConectado(){
	return this->conectado;
}


void Usuario::iniciarSesion(int idSocket) {
	this->idSocket = idSocket;
	this->conectado = true;
}


void Usuario::cerrarSesion() {
	this->idSocket = 0;
	this->conectado = false;
}



