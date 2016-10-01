/*
 * ObjetoMovible.cpp
 *
 *  Created on: 30/9/2016
 *      Author: pablo
 */

#include "ObjetoMovible.h"

ObjetoMovible::ObjetoMovible(Posicion* posicion) {

	this->posicion = posicion;
	this->movimiento = new Movimiento();
}

ObjetoMovible::~ObjetoMovible() {

	delete this->movimiento;
}


void ObjetoMovible::setDireccion(Direccion* nuevaDireccion) {

	this->movimiento->setDireccion(nuevaDireccion);
}


Posicion* ObjetoMovible::getPosicion() {

	return this->posicion;
}


void ObjetoMovible::avanzar() {

	this->posicion = this->movimiento->avanzar(this->posicion);
}

