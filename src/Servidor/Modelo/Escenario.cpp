#include "Escenario.h"

Escenario::Escenario(map<int, Capa*> mapCapas, map<int, Jugador*> mapJugadores) {

	this->mapCapas = mapCapas;
	this->mapJugadores = mapJugadores;
}

Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}


Capa* Escenario::getCapaById(int id) {

	Capa* capa = NULL;

		map<int, Capa*>::iterator it;

		if((it = this->mapCapas.find(id)) != this->mapCapas.end())
			capa = this->mapCapas[id];

		return capa;
}


Jugador* Escenario::getJugadorById(int id) {

	Jugador* jugador = NULL;

		map<int, Jugador*>::iterator it;

		if((it = this->mapJugadores.find(id)) != this->mapJugadores.end())
			jugador = this->mapJugadores[id];

		return jugador;
}


void Escenario::addJugador(Jugador* jugador) {

	this->mapJugadores[jugador->getId()] = jugador;
}
