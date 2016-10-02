#include "EscenarioS.h"

EscenarioS::EscenarioS(map<int, Capa*> mapCapas, map<int, Jugador*> mapJugadores) {

	this->mapCapas = mapCapas;
	this->mapJugadores = mapJugadores;
}

EscenarioS::~EscenarioS() {
	// TODO Auto-generated destructor stub
}


Capa* EscenarioS::getCapaById(int id) {

	Capa* capa = NULL;

		map<int, Capa*>::iterator it;

		if((it = this->mapCapas.find(id)) != this->mapCapas.end())
			capa = this->mapCapas[id];

		return capa;
}


Jugador* EscenarioS::getJugadorById(int id) {

	Jugador* jugador = NULL;

		map<int, Jugador*>::iterator it;

		if((it = this->mapJugadores.find(id)) != this->mapJugadores.end())
			jugador = this->mapJugadores[id];

		return jugador;
}


void EscenarioS::addJugador(Jugador* jugador) {

	this->mapJugadores[jugador->getId()] = jugador;
}
