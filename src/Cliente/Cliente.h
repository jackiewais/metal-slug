#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "ConexionCli.h"

class Cliente:ConexionCli {
private:

	datosConexionStruct datosConexion;

	int seleccConectar();
	int getIpAndPort();
	int selectFromMenu();
	int seleccDesconectar();
	int salir();
	int enviar();
	int recibir();
	int loremIpsum();

public:
	Cliente();
	virtual ~Cliente();
	int runCliente();
};

#endif /* CLIENTE_H_ */
