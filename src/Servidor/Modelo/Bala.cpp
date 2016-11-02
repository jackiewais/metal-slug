/*
 * Bala.cpp
 *
 *  Created on: 02/11/2016
 *      Author: nahue
 */

#include "Bala.h"


Bala::Bala(int x, int y, int dir) {

this->x = x;
this->y = y;
this->direccion = dir;

}

void Bala::mover(){

	this->x++;
	//this->y++;

}
Bala::~Bala() {
	// TODO Auto-generated destructor stub
}

