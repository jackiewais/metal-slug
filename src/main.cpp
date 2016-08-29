#include <iostream>
#include "Servidor.h"
#include "Cliente.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
		cout << "Error\n";
	else {
		if ( argv[1][0] == 's' ) {       // Servidor
			Servidor servidor(3000);
			servidor.escuchar(10);
		} else if(argv[1][0] == 'c') {   // Cliente
			Cliente cliente;
			cliente.conectar("127.0.0.1", 3000);
		}
	}

	return 0;
}
