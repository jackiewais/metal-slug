#include "Jugador.h"


Jugador::Jugador(int id, Posicion* posicion) : ObjetoMovible(posicion) {

	this->id = id;
	this->estado = ConectadoJugador::getEstado();
}

Jugador::~Jugador() {
	// TODO Auto-generated destructor stub
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


//void Jugador::interceptarA(Capa* capa) {

	//capa->interceptarA(this->estado, this);
//}


//void interceptarA(Jugador* jugador) {

	//logica para mostrar al jugador de cada cliente
	//o sea, ocultar al otro jugador cuando estan en la misma posicion sin importar si esta conectado o no
//}

