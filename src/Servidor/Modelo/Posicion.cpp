#include "Posicion.h"
#include <sstream>

using namespace std;



Posicion::Posicion(int x, int y) {

	this->x = x;
	this->y = y;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

int Posicion::getCoordenadaX() {

	return this->x;
}


void Posicion::setCoordenadaX(int x) {

	this->x = x;
}


int Posicion::getCoordenadaY() {

	return this->y;
}


void Posicion::setCoordenadaY(int y) {

	this->y = y;
}


bool Posicion::igualdadDePosicion(Posicion* otraPosicion) {

	return (( this->x == otraPosicion->getCoordenadaX() ) && ( this->y == otraPosicion->getCoordenadaY() ));
}


Posicion* Posicion::sumarPosicion(Posicion* otraPosicion) {

	return new Posicion(this->x + otraPosicion->getCoordenadaX(), this->y + otraPosicion->getCoordenadaY() );
}


string Posicion::getPosConcat() {

    stringstream x,y;
    x << (this->x);
    y << (this->y);
	return (x.str() + ";" + y.str());
}

