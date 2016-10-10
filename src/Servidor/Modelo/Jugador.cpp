#include "Jugador.h"
#include <sstream>

//Jugador::Jugador(int id, Posicion* posicion, int ancho, int alto, int velocidad) : ObjetoMovible(posicion,ancho,alto,velocidad) {
Jugador::Jugador(int id, int velocidad) {

	this->id = id;

}

Jugador::~Jugador() {

}


int Jugador::getId() {

	return this->id;
}

string Jugador::getCodJugador() {
	stringstream idS;
	idS << (this->id);
	return "J" + idS.str();
}

void Jugador::mover(int anchoEscenario, int vecesX) {

	this->posX += (vecesX * this->velocidad);
}


string Jugador::getPosConcat() {

    stringstream x,y;
    x << (this->posX);
    y << (this->posY);
	return (x.str() + ";" + y.str());
}




int Jugador::getPosX() {

	return this->posX;
}


void Jugador::setPosX(int x) {

	this->posX = x;
}


int Jugador::getPosY() {

	return this->posY;
}


void Jugador::setPosY(int y) {

	this->posY = y;
}

