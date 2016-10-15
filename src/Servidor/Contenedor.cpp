#include "Contenedor.h"

#include "Usuario.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


Contenedor::Contenedor() {
}

Contenedor::~Contenedor() {
	map<string, Usuario*>::iterator it;
	Usuario *usuario;

	for(it = this->mapUsuarios.begin(); it != this->mapUsuarios.end(); it++) {
		usuario = it->second;
		delete usuario;
	}
}


void Contenedor::inicializarContenedor(string csv) {
	ImportarCSV *importar = new ImportarCSV();
	string **tablaUsuarios = importar->importar(csv);

	if (tablaUsuarios != NULL) {
		for(int i=0; i < importar->getCantidadUsuarios(); i++) {
			string nombre = tablaUsuarios[i][0];
			string pass = tablaUsuarios[i][1];
			string clave = nombre + ";" + pass;
			Usuario *usuario;
			usuario = new Usuario(i+1,nombre,pass);
			this->mapUsuarios[clave] = usuario;
		}
	}

	//delete[] tablaUsuarios;
	delete importar;
}


void split3(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> split3(const string &s, const char delim) {
    vector<string> elems;
    split3(s, delim, elems);
    return elems;
}


Usuario* Contenedor::autentificar(string message) {

	Usuario *usuario = NULL;
	int i = 0;
	map<string, Usuario*>::iterator it;

	if((it = this->mapUsuarios.find(message)) != this->mapUsuarios.end()) {
		usuario = this->mapUsuarios[message];
		i++;
	}

	if (usuario == NULL) {
		vector<string> vector = split3(message, ';');
		string nombre = vector[0];
		string pass = vector[1];

		//falta chekear que no se repita el nombre de usuario para crear uno nuevo
		usuario = new Usuario(i+1,nombre,pass);
		this->mapUsuarios[message] = usuario;
	}
	return usuario;
}


bool Contenedor::iniciarSesion(string message, int idSocket){

	bool sesionIniciada = false;
	Usuario *usuario = this->autentificar(message);

	if ((usuario != NULL) && (!usuario->isConectado())) {
		this->socket_usuario[idSocket] = usuario;
		usuario->iniciarSesion(idSocket);
		sesionIniciada = true;
	}
	return sesionIniciada;
}


bool Contenedor::cerrarSesion(int idSocket) {

	bool sesionCerrada = false;
	Usuario *usuario = this->getUsuarioBySocket(idSocket);

	cout << "Usuario " << usuario->getNombre() << " Desconectado" << endl;

	if (usuario != NULL) {
		//this->socket_usuario.erase(idSocket);
		usuario->cerrarSesion();
		sesionCerrada = true;
	}
	return sesionCerrada;
}

Usuario* Contenedor::getUsuarioBySocket(int idSocket) {

	Usuario *usuario = NULL;

	map<int, Usuario*>::iterator it;

	if((it = this->socket_usuario.find(idSocket)) != this->socket_usuario.end())
		usuario = this->socket_usuario[idSocket];

	return usuario;
}


string Contenedor::getIdNombresUsuarios(string message) {

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


list<int> Contenedor::getIdOtrosUsuarios(int idUsuarioActual) {

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


void Contenedor::addIdSocketIdJugador(int IdSocket, int idJugador) {

	this->idSocket_idJugador[IdSocket] = idJugador;
}


int Contenedor::getIdJugadorByIdSocket(int idSocket) {

	int idJugador = 0;

	map<int, int>::iterator it;

	if((it = this->idSocket_idJugador.find(idSocket)) != this->idSocket_idJugador.end())
		idJugador = this->idSocket_idJugador[idSocket];

	return idJugador;
}


