#include "EnemigoTaniOh.h"
#include <map>

using namespace std;

EnemigoTaniOh::EnemigoTaniOh(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores)
:Enemigo(id, velocidad, ancho, alto, altoEscenario, mapJugadores,"taniOh")
{
	this->sprite = "taniOh";
	this->vida = 1000;
	this->piso = altoEscenario - 300;
	moverAPosicionInicial();
}

EnemigoTaniOh::~EnemigoTaniOh() {
	// TODO Auto-generated destructor stub
}

void EnemigoTaniOh::mover(int anchoEscenario) {
	Jugador *unJugador;
	map<int, Jugador*>::iterator it = this->mapJugadores->begin();

	if ( it != this->mapJugadores->end() ) {
		unJugador = it->second;
		int distancia = this->posX - unJugador->getPosX();

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

string EnemigoTaniOh::getUtimoChar(){
	if (this->vida >= 600){
		return "C";
	}else{
		return "D";
	}
}

void EnemigoTaniOh::mover(int anchoEscenario, int vecesX) {
	this->posX += (vecesX * this->velocidad);
}

void EnemigoTaniOh::moverAPosicionInicial(){
	this->posX = 800;
	this->posY = this->piso;
	this->estado=PARADO_GUN;
}

bool EnemigoTaniOh::esEnemigoFinal() {
	return true;
}
