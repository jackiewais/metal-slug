#ifndef CONTENEDORUSUARIOS_H_
#define CONTENEDORUSUARIOS_H_

#include "ImportarCSV.h"
#include "Usuario.h"
#include <stdio.h>
#include <map>
#include <string>

using namespace std;

class ContenedorUsuarios {

private:
	ImportarCSV *importar;
	map<string, Usuario*> mapUsuarios;
	map<int, Usuario*> socket_usuario;

	void inicializarContenedor(string csv);
	Usuario* autentificar(string nombre, string pass);

public:
	ContenedorUsuarios(string csv);
	virtual ~ContenedorUsuarios();
	bool iniciarSesion(string nombre, string pass, int idSocket);
	bool cerrarSesion(int idSocket);
	int getCantidadUsuarios();
	Usuario* getUsuarioBySocket(int idSocket);
};

#endif /* CONTENEDORUSUARIOS_H_ */
