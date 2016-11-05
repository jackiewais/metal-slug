#include <string>
#include "LTextureBasic.h"
#include "Numero.h"
#include <iostream>

class Contador {

public:
	Contador(std::string id, int posX, int posY, Numero* numero);
	virtual ~Contador();
	void renderizar();
	int puntaje=234;
	int posX;
	int posY;
	std::string id;
	Numero* numero;


	void actualizarPuntaje(int dif);
};
