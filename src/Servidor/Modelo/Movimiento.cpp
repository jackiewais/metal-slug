/*
 * Movimiento.cpp
 *
 *  Created on: 29/9/2016
 *      Author: pablo
 */

#include "Movimiento.h"
#include "DirDerecha.h"
#include "DirIzquierda.h"


Movimiento::Movimiento(int ancho, int alto, int velocidad) {

	this->ancho = ancho;
	this->alto = alto;
	this->velocidad = velocidad;
}

Movimiento::~Movimiento() {

}


void Movimiento::setDirDerecha() {

	this->direccion = DirDerecha::getDireccion();
}


void Movimiento::setDirIzquierda() {

	this->direccion = DirDerecha::getDireccion();
}


Posicion* Movimiento::mover(Posicion* posicionActual, int anchoEscenario) {

	Posicion* nuevaPos = this->direccion->getSiguientePosicion(posicionActual, this->velocidad,this->ancho,anchoEscenario);

	delete posicionActual;

	return nuevaPos;
}


