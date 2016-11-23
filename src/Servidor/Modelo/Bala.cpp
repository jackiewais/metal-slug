/*
 * Bala.cpp
 *
 *  Created on: 0this->velocidad/11/this->velocidad016
 *      Author: nahue
 */

#include "Bala.h"

Bala::Bala(int x, int y, int dir,int jugador, int velocidad) {

this->x = x;
this->y = y;
this->direccion = dir;
this->velocidad = velocidad;
this->IdJugador = jugador;
this->radio = 10;
}

void Bala::mover(){

	if (this->tipoDeBala == MACHINEGUN){
		switch(this->direccion){
				case RIGHT:
					switch(balaMachine){
					case up:
						this->x +=this->velocidad;
						if(movimientos >=1){
							this->y -=1;
							movimientos = 0;
							}
					break;
					case down :
						this->x +=this->velocidad;
						if(movimientos >=1){
							this->y +=1;
							movimientos = 0;
							}
					break;
					case middle:
					this->x +=this->velocidad;
					break;
					}
		//fin RIgth
				break;
				case LEFT:
					switch(balaMachine){
					case up:
						this->x-=this->velocidad;
						if(movimientos >=1){
							this->y -=1;
							movimientos = 0;
							}
					break;
					case down :
						this->x-=this->velocidad;
						if(movimientos >=1){
							this->y +=1;
							movimientos = 0;
							}
					break;
					case middle:
						this->x-=this->velocidad;
					break;
					}


				break;
				case UP:
					switch(balaMachine){
					case up:
						this->y-=this->velocidad;
						if(movimientos >=2){
							this->x -=1;
							movimientos = 0;
							}
					break;
					case down :
						this->y-=this->velocidad;
						if(movimientos >=2){
							this->x +=1;
							movimientos = 0;
							}
					break;
					case middle:
						this->y-=this->velocidad;
					break;
					}

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

	}else {
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
			this->direccion = RIGHT;
		break;
		case DIAGLEFT:
			this->x-=this->velocidad;
			this->direccion = LEFT;
			break;
	}
	}

	//this->y++;

}


Bala::~Bala() {
	// TODO Auto-generated destructor stub
}

