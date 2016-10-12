#include "EscenarioS.h"
#include <sstream>

EscenarioS::EscenarioS(int alto, int ancho) {

	this->ancho = ancho;
	this->alto = alto;
}

EscenarioS::~EscenarioS() {
	// TODO Auto-generated destructor stub
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


void splitE(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> splitE(const string &s, const char delim) {
    vector<string> elems;
    splitE(s, delim, elems);
    return elems;
}

list<mensajeStruct> EscenarioS::moverJugador(int jugadorId, string mensaje) {
	Jugador* jugador = this->mapJugadores[jugadorId];
	vector<string> result = splitE(mensaje, ';');
	int vecesX = atoi(result[0].c_str());
	string estado = result[1];
	list<mensajeStruct> returnList;

	if (jugador->mover(this->margen,vecesX, estado)) {
		if (!moverEscenario(&returnList)) {
			//Si no se puede mover el escenario, ya que hay un jugador conectado que lo impide
			//entonces el jugador retrocede
			jugador->mover(this->margen,-1, estado);
			returnList.push_back(getMensajeJugador(jugador));
		}
	}
	return returnList;
}

void EscenarioS::aceptarCambios(){
	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		jugador->second->aceptaCambios = true;
	}
}

bool EscenarioS::moverEscenario(list<mensajeStruct>* mainList) {

	bool puedeMover;
	int minPosX = this->distancia;

	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		if (jugador->second->conectado()){
			if (jugador->second->getPosX() < minPosX){
				minPosX = jugador->second->getPosX();
			}
		}
	}

	if (minPosX == 0) {
		puedeMover = false;
	}
	else {
		puedeMover = true;
		int distRecorrida = 1;

		while (distRecorrida <= minPosX) {
			for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador) {
					jugador->second->mover(this->margen,-1, "CAMINA_IZQ");
					mainList->push_back(getMensajeJugador(jugador->second));
			}
			this->avance += distRecorrida;
			mainList->push_back(getMensajeEscenario());
			distRecorrida += 1;
		}
	}
	return puedeMover;
}


mensajeStruct EscenarioS::getMensajeJugador(Jugador* jugador){
	mensajeStruct msjJug;

	msjJug.tipo = JUGADOR_UPD;
	msjJug.message = jugador->getPosConcat();
	msjJug.objectId = jugador->getCodJugador();

	return msjJug;
}

mensajeStruct EscenarioS::getMensajeEscenario(){
	mensajeStruct msjEscenario;

	msjEscenario.tipo = ESCENARIO_UPD;
	msjEscenario.message = this->avance;
	msjEscenario.objectId = "E00";

	return msjEscenario;
}
