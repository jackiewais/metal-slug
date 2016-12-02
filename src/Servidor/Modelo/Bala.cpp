/*
 * Bala.cpp
 *
 *  Created on: 0this->velocidad/11/this->velocidad016
 *      Author: nahue
 */

#include "Bala.h"
#include <iostream>

using namespace std;

Bala::Bala(int x, int y, int dir,int jugador, int velocidad) {

this->x = x;
this->y = y;
this->direccion = dir;
this->velocidad = velocidad;
this->IdJugador = jugador;
this->radio = 10;
}
Bala::Bala(int x, int y, int dir,int jugador, int velocidad, bool parabola) {

this->x = x;
this->y = y;
this->direccion = dir;
this->velocidad = velocidad;
this->IdJugador = jugador;
this->radio = 10;
this->balaParabola = parabola;

//cargo la parabola

}


void Bala::mover(){
	int parabolaX;
	int parabolaY;
	switch (this->tipoDeBala){
	case MACHINEGUN:
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
	break;
	case GUN:
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
			case DOWN:

				this->y += this->velocidad;
				break;
			case DIAGLEFTDOWN:

						this->y += this->velocidad;
						this->x -= this->velocidad;
						break;
			case DIAGRIGHTDOWN:

						this->y += this->velocidad;
						this->x += this->velocidad;

						break;
		}
		break;
		case SHOOTGUN:
			switch(this->direccion){
						case RIGHT:
							this->x+=this->velocidad;
						break;
						case LEFT:
							this->x-=this->velocidad;
						break;
						case DIAGRIGHT:
										this->x+=this->velocidad;
										this->direccion = RIGHT;
									break;
									case DIAGLEFT:
										this->x-=this->velocidad;
										this->direccion = LEFT;
										break;
									case DOWN:
						case UP:
							this->y-=this->velocidad;
						break;
			}
			break;
		case TANIOHGUN:
					parabolaX = variableParabola;
					parabolaY = ((variableParabola -4)*(variableParabola -4)) + 400;
					this->x-=10;
					this->y = parabolaY;

					cout << "("<< x << "," << y << ")" << endl;
					if(variableParabola <=14){
					variableParabola++;
					}
		break;
		case BOMB:
			switch(this->direccion){
						case RIGHT:
							parabolaX = variableParabola;
							parabolaY = ((variableParabola -5)*(variableParabola -5)) + 50;
							this->x +=3;
							this->y = parabolaY;

							cout << "("<< x << "," << y << ")" << endl;
							if(variableParabola <=100){
							variableParabola++;

							}
						break;
						case LEFT:
							parabolaX = variableParabola;
							parabolaY = ((variableParabola -5)*(variableParabola -5)) + 50;
							this->x-=3;
							this->y = parabolaY;

							cout << "("<< x << "," << y << ")" << endl;
							if(variableParabola <=100){
							variableParabola++;


							}
						break;
						case DOWN:
							this->y += 10;
						break;

		break;
	}
	}



	//this->y++;

}


Bala::~Bala() {
	// TODO Auto-generated destructor stub
}

