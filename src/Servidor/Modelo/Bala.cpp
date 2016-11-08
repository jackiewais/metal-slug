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

	switch(this->direccion){
		case RIGHT:
			this->x+=2;
		break;
		case LEFT:
			this->x-=2;
		break;
		case UP:
			this->y-=2;
		break;
		case DIAGRIGHT:
			this->x+=2;
			this->y-=2;
		break;
		case DIAGLEFT:
			this->x-=2;
			this->y-=2;
		break;
	}

	//this->y++;

}
Bala::~Bala() {
	// TODO Auto-generated destructor stub
}

