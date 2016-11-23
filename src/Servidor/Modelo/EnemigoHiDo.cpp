#include "EnemigoHiDo.h"

EnemigoHiDo::EnemigoHiDo(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores)
:Enemigo(id, velocidad, ancho, alto, altoEscenario, mapJugadores)
{
	this->sprite = "hiDo";
	this->vida = 1000;
	moverAPosicionInicial();
}

EnemigoHiDo::~EnemigoHiDo() {
	// TODO Auto-generated destructor stub
}

void EnemigoHiDo::mover(int anchoEscenario) {
	Jugador *unJugador;
	map<int, Jugador*>::iterator it = this->mapJugadores->begin();

	if ( it != this->mapJugadores->end() ) {
		unJugador = it->second;
		int distancia = this->posX + (this->ancho/2) - unJugador->getPosX();

		if ( distancia > this->distanciaHastaLaQueSeAcercaAJugador ) {
			this->mover(anchoEscenario, -1);
		} else if ( distancia < -this->distanciaHastaLaQueSeAcercaAJugador ) {
			this->mover(anchoEscenario, 1);
		} else if ( (this->posX < 0) && (this->posX < unJugador->getPosX()) ) {
			this->mover(anchoEscenario, 1);
		} else if ( (this->posX > (anchoEscenario - this->ancho)) && (this->posX > unJugador->getPosX()) ) {
			this->mover(anchoEscenario, -1);
		} else {
			this->mover(anchoEscenario, 0);
		}

	}
}


string EnemigoHiDo::getUtimoChar(){
	if (this->vida >= 600){
		return "C";
	}else{
		return "D";
	}
}

void EnemigoHiDo::mover(int anchoEscenario, int vecesX) {
	this->posX += (vecesX * this->velocidad);
}

void EnemigoHiDo::moverAPosicionInicial(){
	this->posX = -this->ancho;
	this->posY = 50;
	this->estado=PARADO_GUN;
}

bool EnemigoHiDo::esEnemigoFinal() {
	return true;
}
