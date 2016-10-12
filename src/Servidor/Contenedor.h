#ifndef Contenedor_H_
#define Contenedor_H_

#include "ImportarCSV.h"
#include "Usuario.h"
#include <stdio.h>
#include <map>
#include <string>
#include <list>

using namespace std;

class Contenedor {

private:
	map<string, Usuario*> mapUsuarios;
	map<int, int> idSocket_idJugador;

	Usuario* autentificar(string message);

public:
	map<int, Usuario*> socket_usuario;

	Contenedor();
	virtual ~Contenedor();
	void inicializarContenedor(string csv);
	bool iniciarSesion(string message, int idSocket);
	bool cerrarSesion(int idSocket);
	Usuario* getUsuarioBySocket(int idSocket);
	string getIdNombresUsuarios(string message);
	list<int> getIdOtrosUsuarios(int idUsuarioActual);
	void addIdSocketIdJugador(int idSocket, int idJugador);
	int getIdJugadorByIdSocket(int idSocket);
};

#endif /* Contenedor_H_ */
