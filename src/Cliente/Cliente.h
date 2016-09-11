#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "ConexionCli.h"
#include "../Common/Mensajeria.h"
#include <iostream>
#include <string.h>

class Cliente:ConexionCli {
private:

	 datosConexionStruct datosConexion;
	 ConexionCli conexionCli;
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
public:
	Cliente();
	virtual ~Cliente();
	int runCliente();
};

#endif /* CLIENTE_H_ */
