#include "ContenedorUsuarios.h"
#include "Usuario.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


ContenedorUsuarios::ContenedorUsuarios() {
	this->importar = new ImportarCSV();
}

ContenedorUsuarios::~ContenedorUsuarios() {
	delete importar;
	//delete[] this->importar;
}


void ContenedorUsuarios::inicializarContenedor(string csv) {

	string **tablaUsuarios = this->importar->importar(csv);

	for(int i=0; i < this->importar->getCantidadUsuarios(); i++) {
		string nombre = tablaUsuarios[i][0];
		string pass = tablaUsuarios[i][1];
		string clave = nombre + ";" + pass;
		Usuario *usuario;
		usuario = new Usuario(i+1,nombre,pass);
		this->mapUsuarios[clave] = usuario;
	}

	delete[] tablaUsuarios;
}


Usuario* ContenedorUsuarios::autentificar(string message) {

	Usuario *usuario = NULL;

	map<string, Usuario*>::iterator it;

	if((it = this->mapUsuarios.find(message)) != this->mapUsuarios.end())
		usuario = this->mapUsuarios[message];

	return usuario;
}


bool ContenedorUsuarios::iniciarSesion(string message, int idSocket){

	bool sesionIniciada = false;
	Usuario *usuario = this->autentificar(message);

	if (usuario != NULL) {
		this->socket_usuario[idSocket] = usuario;
		usuario->iniciarSesion(idSocket);
		sesionIniciada = true;
	}
	return sesionIniciada;
}


bool ContenedorUsuarios::cerrarSesion(int idSocket) {

	bool sesionCerrada = false;
	Usuario *usuario = this->getUsuarioBySocket(idSocket);

	if (usuario != NULL) {
		this->socket_usuario.erase(idSocket);
		usuario->cerrarSesion();
		sesionCerrada = true;
	}
	return sesionCerrada;
}


int ContenedorUsuarios::getCantidadUsuarios() {

	return this->importar->getCantidadUsuarios();
}


Usuario* ContenedorUsuarios::getUsuarioBySocket(int idSocket) {

	Usuario *usuario = NULL;

	map<int, Usuario*>::iterator it;

	if((it = this->socket_usuario.find(idSocket)) != this->socket_usuario.end())
		usuario = this->socket_usuario[idSocket];

	return usuario;
}


string ContenedorUsuarios::getIdNombresUsuarios(string message) {

	map<string, Usuario*>::iterator it;
	Usuario *usuario;
	string idNombresUsuarios = "";
	int idUsuario;

	for(it = this->mapUsuarios.begin(); it != this->mapUsuarios.end(); it++) {

		if (message != it->first) {
			usuario = it->second;

			idUsuario = usuario->getIdUsuario();
			stringstream ss;
			ss << idUsuario;

			idNombresUsuarios += ss.str() + "_" + usuario->getNombre() + ";";
		}
	}

	return idNombresUsuarios;
}


list<int> ContenedorUsuarios::getIdOtrosUsuarios(int idUsuarioActual) {

	list<int> idOtrosUsuarios;
	map<string, Usuario*>::iterator it;
	Usuario *usuario;
	string idNombresUsuarios = "";
	int idUsuario;

	for(it = this->mapUsuarios.begin(); it != this->mapUsuarios.end(); it++) {

		usuario = it->second;
		idUsuario = usuario->getIdUsuario();
		if (idUsuarioActual != idUsuario) {
			idOtrosUsuarios.push_back(idUsuario);
		}
	}
	return idOtrosUsuarios;
}
