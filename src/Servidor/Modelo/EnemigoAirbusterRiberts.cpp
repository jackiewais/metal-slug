#include "EnemigoAirbusterRiberts.h"
#include <map>

using namespace std;

EnemigoAirbusterRiberts::EnemigoAirbusterRiberts(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores)
:Enemigo(id, velocidad, ancho, alto, altoEscenario, mapJugadores)
{
	this->sprite = "airbus";
	moverAPosicionInicial();
}

EnemigoAirbusterRiberts::~EnemigoAirbusterRiberts() {
	// TODO Auto-generated destructor stub
}

void EnemigoAirbusterRiberts::mover(int anchoEscenario) {
	Jugador *unJugador;
	map<int, Jugador*>::iterator it = this->mapJugadores->begin();

	if ( it != this->mapJugadores->end() ) {
		unJugador = it->second;


		if ( (this->posX - unJugador->getPosX()) > this->distanciaHastaLaQueSeAcercaAJugador ) {
			this->mover(anchoEscenario, -1, "PARADO_GUN");
		} else if ( (this->posX - unJugador->getPosX()) < -this->distanciaHastaLaQueSeAcercaAJugador ) {
			this->mover(anchoEscenario, 1, "PARADO_GUN");
		} else if ( (this->posX < 0) && (this->posX < unJugador->getPosX()) ) {
			this->mover(anchoEscenario, 1, "PARADO_GUN");
		} else if ( (this->posX > (anchoEscenario - this->ancho)) && (this->posX > unJugador->getPosX()) ) {
			this->mover(anchoEscenario, -1, "PARADO_GUN");
		} else {
			this->mover(anchoEscenario, 0, "PARADO_GUN");
		}

	}
}

void EnemigoAirbusterRiberts::mover(int anchoEscenario, int vecesX, string accion) {
	this->posX += (vecesX * this->velocidad);
}

void EnemigoAirbusterRiberts::moverAPosicionInicial(){
	this->posX = -this->ancho;
	this->posY = 50;
	this->estado=PARADO_GUN;
}

bool EnemigoAirbusterRiberts::esEnemigoFinal() {
	return true;
}
