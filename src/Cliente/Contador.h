#include <string>
#include "LTextureBasic.h"
#include "Numero.h"
#include "Progreso.h"

#include "Label.h"
#include <iostream>

class Contador {

public:
	Contador(std::string id, int posX, int posY, Numero* numero, Progreso* progreso, Label* lbalas);
	virtual ~Contador();
	void renderizar();
	int puntaje=234;
	int vida=100;
	int balas=-1;
	int posX;
	int posY;
	std::string id;
	Numero* numero;
	Progreso* progreso;
	Label* lbalas;

	void actualizarPuntaje(int dif);
	void actualizarVida(int dif);

	void renderizarCantBalas();
};
