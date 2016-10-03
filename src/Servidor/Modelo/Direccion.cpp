#include "Direccion.h"

Direccion::Direccion(Posicion* direccion) {

	this->direccion = direccion;
}

Direccion::~Direccion() {
	this->direccion;
}

// AGREGO ESTA FUNCION PARA QUE NO ROMPA AL COMPILAR (FALTA IMPLEMENTAR)
Posicion* Direccion::getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario) {
	return NULL;
}
