/*
 * Bala.h
 *
 *  Created on: 02/11/2016
 *      Author: nahue
 */

#ifndef BALA_H_
#define BALA_H_
#include "../../Common/Modelo.h"
class Bala {
private:

	int direccion;
	int velocidad;


public:
	weapon tipoDeBala;
	int movimientos = 0; //ORRIBLE (SIN H). LO USO PARA MATAR LA BALA DE SHOOTGUN. POR AHORA ES ASI
	int IdJugador;
	int x,y;
	void mover();
	Bala(int x,int y, int dir,int jugador);
	virtual ~Bala();
};

#endif /* BALA_H_ */
