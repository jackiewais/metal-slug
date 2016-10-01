/*
 * Posicion.cpp
 *
 *  Created on: 29/9/2016
 *      Author: pablo
 */

#include "Posicion.h"

Posicion::Posicion(int x, int y) {

	this->x = x;
	this->y = y;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

int Posicion::getCoordenadaX() {

	return this->x;
}


int Posicion::getCoordenadaY() {

	return this->y;
}


bool Posicion::igualdadDePosicion(Posicion otraPosicion) {

	return (( this->x == otraPosicion.getCoordenadaX() ) && ( this->y == otraPosicion.getCoordenadaY() ));
}
