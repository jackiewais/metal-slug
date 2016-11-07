/*
 * Bala.cpp
 *
 *  Created on: 02/11/2016
 *      Author: nahue
 */

#include "Bala.h"

Bala::Bala(int x, int y, int dir,Jugador* jugador) {

this->x = x;
this->y = y;
this->direccion = dir;
this->jugador = jugador;

}

void Bala::mover(){

	this->x+=2;
	//this->y++;

}
Bala::~Bala() {
	// TODO Auto-generated destructor stub
}

