/*
 * Bala.h
 *
 *  Created on: 02/11/2016
 *      Author: nahue
 */


#ifndef BALA_H_
#define BALA_H_

#include "../../Common/Modelo.h"
#include <iostream>
#include <list>
using namespace std;
class Bala {
private:

	struct pos{
		int x;
		int y;
	};

	int velocidad;
	bool balaParabola;

	int variableParabola=0;

public:
	int radio;
	balaMachineGun balaMachine;
	weapon tipoDeBala;
	int movimientos = 0; //ORRIBLE (SIN H). LO USO PARA MATAR LA BALA DE SHOOTGUN. POR AHORA ES ASI
	int IdJugador;
	int x,y;
	int direccion;
	void mover();
	Bala(int x,int y, int dir,int jugador,int velocidad);
	Bala(int x,int y, int dir,int jugador,int velocidad,bool parabola);
	virtual ~Bala();
};

#endif /* BALA_H_ */
