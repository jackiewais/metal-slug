#include "ContenedorUsuarios.h"
#include "Usuario.h"
#include <stdio.h>
#include <string>

using namespace std;


ContenedorUsuarios::ContenedorUsuarios() {

	this->importar = new ImportarCSV();
}

ContenedorUsuarios::~ContenedorUsuarios() {

	delete[] this->importar;
}


void ContenedorUsuarios::inicializarContenedor(string csv) {

	string **tablaUsuarios = this->importar->importar(csv);

	for(int i=0; i < this->importar->getCantidadUsuarios(); i++) {
		string nombre = tablaUsuarios[i][0];
		string pass = tablaUsuarios[i][1];
		string clave = nombre + pass;
		Usuario *usuario;
		usuario = new Usuario(i+1,nombre,pass);
		this->mapUsuarios[clave] = usuario;
	}

	delete[] tablaUsuarios;
}


Usuario* ContenedorUsuarios::autentificar(string nombre, string pass) {

	Usuario *usuario = NULL;
	string clave = nombre + pass;

	map<string, Usuario*>::iterator it;

	if((it = this->mapUsuarios.find(clave)) != this->mapUsuarios.end())
		usuario = this->mapUsuarios[clave];

	return usuario;
}


bool ContenedorUsuarios::iniciarSesion(string nombre, string pass, int idSocket){

	bool sesionIniciada = false;
	Usuario *usuario = this->autentificar(nombre, pass);

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
