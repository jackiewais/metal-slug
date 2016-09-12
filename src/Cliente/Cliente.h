#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "ConexionCli.h"
#include "../Common/Mensajeria.h"
#include "../Common/Log.h"
#include <iostream>
#include <string.h>
#include <map>
#include <list>

class Cliente:ConexionCli {
private:

	 datosConexionStruct datosConexion;
	 ConexionCli conexionCli;
	 bool semaforoReceive = false;
	 map<int, string> mapIdNombreUsuario;
	 int seleccConectar();
	int getIpAndPort();
	int selectFromMenu();
	int seleccDesconectar();
	int salir();
	int enviar();
	int recibir();
	int loremIpsum();
	int getUsuarioYContrasenia(std::string &usuario, std::string &contrasenia);
	static void *recvMessage(void * arg);
	void imprimirConsigna();

public:
	Cliente();
	virtual ~Cliente();
	int runCliente();
	string getNombreUsuarioById(int idUsuario);
	list<int> getIdUsuarios();
};

#endif /* CLIENTE_H_ */
