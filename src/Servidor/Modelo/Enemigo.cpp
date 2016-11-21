#include "Enemigo.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;


Enemigo::Enemigo(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores) {
	this->id = id;
	this->velocidad = velocidad;
	this->velSalto = velocidad*2;
	this->ancho = ancho;
	this->alto = alto;
	this->piso = altoEscenario - 150;
	this->topeSalto = piso-100;
	this->plataforma = topeSalto + 40;
	this->mapJugadores = mapJugadores;
	this->distanciaHastaLaQueSeAcercaAJugador = 10 + rand() % (801 - 10);
	this->avanceEscenarioBloqueado = false;
	this->sprite = "jugador4";

	moverAPosicionInicial();
}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

bool Enemigo::estaSaltando() {
	return (this->estado == SALTA_DER_GUN|| this->estado == SALTA_IZQ_GUN);
}

void Enemigo::mover(int anchoEscenario) {
	Jugador *unJugador;
	map<int, Jugador*>::iterator it = this->mapJugadores->begin();

	if ( it != this->mapJugadores->end() ) {
		unJugador = it->second;


		if ( (this->posX - unJugador->getPosX()) > this->distanciaHastaLaQueSeAcercaAJugador ) {
			this->mover(anchoEscenario, -1, "CAMINA_IZQ");
		} else if ( (this->posX - unJugador->getPosX()) < -this->distanciaHastaLaQueSeAcercaAJugador ) {
			this->mover(anchoEscenario, 1, "CAMINA_DER");
		} else if ( (this->posX < 0) && (this->posX < unJugador->getPosX()) ) {
			this->mover(anchoEscenario, 1, "CAMINA_DER");
		} else if ( (this->posX > (anchoEscenario - this->ancho)) && (this->posX > unJugador->getPosX()) ) {
			this->mover(anchoEscenario, -1, "CAMINA_IZQ");
		} else {
			this->mover(anchoEscenario, 0, "PARADO_GUN");
		}

	}
}

void Enemigo::mover(int anchoEscenario, int vecesX, string accion) {

	if (accion=="SALTA"){
		this->estado = (vecesX >= 0)?SALTA_DER_GUN:SALTA_IZQ_GUN;
	}

	manejarSalto();

	if (vecesX == 0){
		if (!estaSaltando()){
			this->estado = PARADO_GUN;
		}
	}else{
		if (!estaSaltando()){
			this->estado =  (vecesX > 0)?CAMINA_DER_GUN:CAMINA_IZQ_GUN;
		}

		this->posX += (vecesX * this->velocidad);
	}
}

void Enemigo::manejarSalto(){
	if (estaSaltando()){
		this->posY += (velSalto * factorSalto);
		if (this->posY < topeSalto){
			factorSalto = 1;
		}else if (this-> posY > piso){
			factorSalto = -1;
			this-> posY = piso;
			this->estado = PARADO_GUN;
		}else if (this->posY ==plataforma && factorSalto == 1 && this->posX > 100 && this->posX < 200){
			factorSalto = -1;
			this-> posY = plataforma;
			this->estado = PARADO_GUN;
		}
	}else{
		if (this->posY ==plataforma && this->posX < 100) {
			factorSalto = 1;
			this->estado = SALTA_IZQ_GUN;
		}else if(this->posY ==plataforma && this->posX > 200){
			factorSalto = 1;
			this->estado = SALTA_DER_GUN;
		}
	}

}

void Enemigo::moverAPosicionInicial(){
	this->posX = 800;
	this->posY = piso;
	this->estado=PARADO_GUN;
}

string Enemigo::getStringMensajeUpdate() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
    estado << this->estado;
	return (x.str() + ";" + y.str() + ";" + estado.str() + ";C");
}

string Enemigo::getStringMensajeNew() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
	return (this->sprite + ";" + x.str() + ";" + y.str());
}

string Enemigo::getCodEnemigo() {
	stringstream idS;
	idS << (this->id);
	return "T" + idS.str();
}

void Enemigo::retrocederSegunAvanceEscenario(int avance) {
	this->posX -= avance;
}

void Enemigo::bloquearAvanceEscenario() {
	this->avanceEscenarioBloqueado = true;
}

bool Enemigo::estaBloqueadoElAvanceDelEscenario(int anchoEscenario) {
	if (this->avanceEscenarioBloqueado) {
		return true;
	}
	return false;
}

void Enemigo::aparecerPorIzquierda() {
	this->posX = 0;
}

bool Enemigo::esEnemigoFinal() {
	return false;
}
