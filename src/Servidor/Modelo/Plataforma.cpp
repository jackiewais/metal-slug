/*
 * Plataforma.cpp
 *
 *  Created on: 06/11/2016
 *      Author: silvia
 */
#include "Plataforma.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <map>

using namespace std;


Plataforma::Plataforma(int id,string imagen, int velocidad, int posXP, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores)
{
	this->id = id;
	this->imagen= imagen;
	this->ancho = ancho;
	this->alto = alto;
	this->velocidad = velocidad;
	this->posX = posXP;
	this->avanceEscenarioBloqueado = false;
	this->piso = altoEscenario - 125;
	this->mapJugadores = mapJugadores;
	moverAPosicionInicial();

}
Plataforma::~Plataforma()
{
}
void Plataforma::moverAPosicionInicial(){
	this->posY = piso;
	this->estado=PARADO_GUN;
}

string Plataforma::getStringMensajeUpdate() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
    estado << this->estado;
	return (x.str() + ";" + y.str() + ";" + estado.str() + ";C");
}
string Plataforma::getStringMensajeNew() {
    stringstream x,y,estado;
    x << (this->posX);
    y << (this->posY);
	return (this->imagen+ ";" + x.str() + ";" + y.str());
}
string Plataforma::getCodPlataforma() {
	stringstream idS;
	idS << (this->id);
	return "P" + idS.str();
}
void Plataforma::bloquearAvanceEscenario() {
	this->avanceEscenarioBloqueado = true;
}
void Plataforma::retrocederSegunAvanceEscenario(int avance) {
	this->posX -= (avance + this->velocidad*2);
}
bool Plataforma::estaBloqueadoElAvanceDelEscenario(int anchoEscenario) {
	if ( this->avanceEscenarioBloqueado && (this->posX < (anchoEscenario - this->ancho)) ) {
		return true;
	}
	return false;
}

int Plataforma::getPosX() {

	return this->posX;
}
int Plataforma::getAncho() {

	return this->ancho;
}
int Plataforma::getPiso() {

	return this->piso;
}


