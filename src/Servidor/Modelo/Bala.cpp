/*
 * Bala.cpp
 *
 *  Created on: 0this->velocidad/11/this->velocidad016
 *      Author: nahue
 */

#include "Bala.h"

Bala::Bala(int x, int y, int dir,int jugador) {

this->x = x;
this->y = y;
this->direccion = dir;
this->velocidad = 10;
this->IdJugador = jugador;
}

void Bala::mover(){

	switch(this->direccion){
		case RIGHT:
			this->x+=this->velocidad;
		break;
		case LEFT:
			this->x-=this->velocidad;
		break;
		case UP:
			this->y-=this->velocidad;
		break;
		case DIAGRIGHT:
			this->x+=this->velocidad;
			this->y-=this->velocidad;
		break;
		case DIAGLEFT:
			this->x-=this->velocidad;
			this->y-=this->velocidad;
		break;
	}

	//this->y++;

}


Bala::~Bala() {
	// TODO Auto-generated destructor stub
}

