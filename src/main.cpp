#include <iostream>
#include "Servidor/Servidor.h"
#include "Cliente/Cliente.h"

using namespace std;

int main(int argc, char *argv[])
{

	string cliOrSrv;
	bool ok = false;

	if (argc == 2) {
		cliOrSrv = argv[1][0];
		ok = (cliOrSrv == "c" || cliOrSrv == "s");
	}

	while (!ok){
		cout << "Ingrese 'c' para cliente, 's' para servidor" << endl;
		cin >> cliOrSrv;
		ok = (cliOrSrv == "c" || cliOrSrv == "s");
	}

	if (cliOrSrv == "c"){
		Cliente* cliente = new Cliente;
		cliente->runCliente();
		delete cliente;
	}else{
		Servidor* servidor = new Servidor;
		servidor->runServer();
		delete servidor;
	}

	return 0;
}
