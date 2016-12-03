#include "EnemigoAirbusterRiberts.h"
#include <map>

using namespace std;

EnemigoAirbusterRiberts::EnemigoAirbusterRiberts(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores)
:Enemigo(id, velocidad, ancho, alto, altoEscenario, mapJugadores, "airbus")
{
	this->sprite = "airbus";
	this->vida = 1000;
	this->idDeProxEnemigoALanzar = 1000;
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
		int distancia = this->posX + (this->ancho/2) - unJugador->getPosX();

		/*if ( distancia <= 0 ) {
			this->estado = CAMINA_DER_GUN;
		} else {
			this->estado = CAMINA_IZQ_GUN;
		}*/

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


string EnemigoAirbusterRiberts::getUtimoChar(){
	if (this->vida >= 600){
		return "C";
	}else{
		return "D";
	}
}

void EnemigoAirbusterRiberts::mover(int anchoEscenario, int vecesX) {
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

Enemigo* EnemigoAirbusterRiberts::lanzarEnemigo(){
	Enemigo *enemigo = NULL;
	if ( (this->posX >= 0) && (this->idDeProxEnemigoALanzar == 1000) ) {
		enemigo = new Enemigo(this->idDeProxEnemigoALanzar,this->velocidad,74,98,this->piso+150,this->mapJugadores,"enemigo");
		enemigo->saltandoDeAvion(this->posX, this->posY);
		this->idDeProxEnemigoALanzar++;
	}
	return enemigo;
}
