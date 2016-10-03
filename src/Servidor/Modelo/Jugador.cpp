#include "Jugador.h"


Jugador::Jugador(int id, Posicion* posicion, int ancho, int alto, int velocidad) : ObjetoMovible(posicion,ancho,alto,velocidad) {

	this->id = id;
	this->estado = ConectadoJugador::getEstado();
}

Jugador::~Jugador() {
	this->estado;
}


int Jugador::getId() {

	return this->id;
}


EstadoJugador* Jugador::getEstado() {

	return this->estado;
}


void Jugador::cambiarEstado() {

	this->estado = this->estado->getNuevoEstado();
}



string Jugador::getPosConcat(){
	//return this->posicion->getPosConcat();
}

//void Jugador::interceptarA(Capa* capa) {

	//capa->interceptarA(this->estado, this);
//}

