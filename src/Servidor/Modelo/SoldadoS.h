#ifndef SOLDADOS_H_
#define SOLDADOS_H_

#include <iostream>

class SoldadoS {
//Soldado server

public:
	std::string id;
	int posX;
	int posY;
	int velocidad = 10;
	int anchoSold;
	int altoSold;
	int anchoEscenario;

	void moverDerecha();
	void moverIzquierda();

};

#endif
