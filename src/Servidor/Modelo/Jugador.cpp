#include "Jugador.h"


Jugador::Jugador(int id, Posicion* posicion, int ancho, int alto, int velocidad) : ObjetoMovible(posicion,ancho,alto,velocidad) {

	this->id = id;
}

Jugador::~Jugador() {

}


int Jugador::getId() {

	return this->id;
}


string Jugador::getPosConcat(){
	return this->getPosicion()->getPosConcat();
}


