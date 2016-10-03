/*
 * Movimiento.cpp
 *
 *  Created on: 29/9/2016
 *      Author: pablo
 */

#include "Movimiento.h"


Movimiento::Movimiento(int ancho, int alto, int velocidad) {

	this->ancho = ancho;
	this->alto = alto;
	this->velocidad = velocidad;
}

Movimiento::~Movimiento() {

}


Posicion* Movimiento::mover(Posicion* posicionActual, Direccion* direccion, int anchoEscenario) {

	Posicion* nuevaPos = direccion->getSiguientePosicion(posicionActual, this->velocidad,this->ancho,anchoEscenario);

	delete posicionActual;

	return nuevaPos;
}


