/*
 * Bala.h
 *
 *  Created on: 02/11/2016
 *      Author: nahue
 */

#ifndef BALA_H_
#define BALA_H_
#include "../Modelo/Jugador.h"

class Bala {
private:

	int direccion;


public:
	Jugador* jugador;
	int x,y;
	void mover();
	Bala(int x,int y, int dir, Jugador * jugador);
	virtual ~Bala();
};

#endif /* BALA_H_ */
