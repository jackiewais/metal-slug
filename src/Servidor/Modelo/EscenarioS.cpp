#include "EscenarioS.h"
#include "Direccion.h"
#include "DirDerecha.h"
#include "DirIzquierda.h"


EscenarioS::EscenarioS(int ancho, int alto, map<int, Capa*> mapCapas, map<int, Jugador*> mapJugadores) {

	this->mapCapas = mapCapas;
	this->mapJugadores = mapJugadores;
	this->ancho = ancho;
	this->alto = alto;
}

EscenarioS::EscenarioS(){}


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


list<mensajeStruct> EscenarioS::moverJugador(int jugadorId, string direccion){
	Jugador* jugador = this->mapJugadores[jugadorId];

	list<mensajeStruct> returnList;
	mensajeStruct msjJug;

	if (direccion == "DERECHA"){
		jugador->mover(new DirDerecha(), this->ancho);

	}else if (direccion == "IZQUIERDA"){
		jugador->mover(new DirIzquierda(), this->ancho);
	}

	msjJug.tipo = JUGADOR_UPD;
	msjJug.message = jugador->getPosConcat();

	returnList.push_back(msjJug);
	return returnList;
}
