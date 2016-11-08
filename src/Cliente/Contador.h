#include <string>
#include "LTextureBasic.h"
#include "Numero.h"
#include "Progreso.h"

#include "Label.h"
#include <iostream>

class Contador {

public:
	Contador(std::string id, int posX, int posY, Numero* numero, Progreso* progreso, Label* lbalas, int puntaje,int vida,int municion);
	virtual ~Contador();
	void renderizar();
	int puntaje;
	int vida;
	int balas;
	int posX;
	int posY;
	std::string id;
	Numero* numero;
	Progreso* progreso;
	Label* lbalas;

	void actualizarPuntaje(int nuevo_valor);
	void actualizarVida(int nuevo_valor);
	void actualizarMunicion(int nuevo_valor);

	void actualizarDatos(int puntaje, int vida, int municiones);

	void renderizarCantBalas();
};
