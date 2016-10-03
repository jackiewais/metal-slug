/*
 * ObjetoMovible.cpp
 *
 *  Created on: 30/9/2016
 *      Author: pablo
 */

#include "ObjetoMovible.h"

ObjetoMovible::ObjetoMovible(Posicion* posicion, int ancho, int alto, int velocidad) {

	this->posicion = posicion;
	this->movimiento = new Movimiento(ancho,alto,velocidad);
}

ObjetoMovible::~ObjetoMovible() {

	delete this->movimiento;
	delete this->posicion;
}


Posicion* ObjetoMovible::getPosicion() {

	return this->posicion;
}


Movimiento* ObjetoMovible::getMovimiento() {

	return this->movimiento;
}


void ObjetoMovible::mover(int anchoEscenario) {

	this->posicion = this->movimiento->mover(this->posicion,anchoEscenario);
}

