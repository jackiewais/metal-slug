/*
 * Movimiento.cpp
 *
 *  Created on: 29/9/2016
 *      Author: pablo
 */

#include "Movimiento.h"

Movimiento::Movimiento() {
	// TODO Auto-generated constructor stub
}

Movimiento::~Movimiento() {
	// TODO Auto-generated destructor stub
}


void Movimiento::setDireccion(Direccion* direccion) {

	this->direccion = direccion;
}


Posicion* Movimiento::avanzar(Posicion* posicionActual) {

	//logica para avanzar segun direccion
	delete posicionActual;
	return new Posicion(0,0);
}


