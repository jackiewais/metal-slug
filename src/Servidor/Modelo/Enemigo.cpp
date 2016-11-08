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

	moverAPosicionInicial();
}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

bool Enemigo::estaSaltando() {
	return (this->estado == SALTA_DER || this->estado == SALTA_IZQ);
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
		} else {
			this->mover(anchoEscenario, 0, "PARADO");
		}

	}
}

void Enemigo::mover(int anchoEscenario, int vecesX, string accion) {

	if (accion=="SALTA"){
		this->estado = (vecesX >= 0)?SALTA_DER:SALTA_IZQ;
	}

	manejarSalto();

	if (vecesX == 0){
		if (!estaSaltando()){
			this->estado = PARADO;
		}
	}else{
		if (!estaSaltando()){
			this->estado =  (vecesX > 0)?CAMINA_DER:CAMINA_IZQ;
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
			this->estado = PARADO;
		}else if (this->posY ==plataforma && factorSalto == 1 && this->posX > 100 && this->posX < 200){
			factorSalto = -1;
			this-> posY = plataforma;
			this->estado = PARADO;
		}
	}else{
		if (this->posY ==plataforma && this->posX < 100) {
			factorSalto = 1;
			this->estado = SALTA_IZQ;
		}else if(this->posY ==plataforma && this->posX > 200){
			factorSalto = 1;
			this->estado = SALTA_DER;
		}
	}

}

void Enemigo::moverAPosicionInicial(){
	this->posX = 800;
	this->posY = piso;
	this->estado=PARADO;
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
	return ("jugador4;" + x.str() + ";" + y.str());
}

string Enemigo::getCodEnemigo() {
	stringstream idS;
	idS << (this->id);
	return "T" + idS.str();
}

void Enemigo::retrocederSegunAvanceEscenario(int avance) {
	this->posX -= avance;
}
