#include "Jugador.h"
#include <sstream>

Jugador::Jugador(int id, Posicion* posicion, int ancho, int alto, int velocidad) : ObjetoMovible(posicion,ancho,alto,velocidad) {

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


string Jugador::getPosConcat(){
	return this->getPosicion()->getPosConcat();
}


