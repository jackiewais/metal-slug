#include "Direccion.h"

Direccion::Direccion(Posicion* direccion) {

	this->direccion = direccion;
}

Direccion::~Direccion() {
	// TODO Auto-generated destructor stub
}

Posicion* Direccion::getDireccion() {

	return this->direccion;
}
