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

list<mensajeStruct> EscenarioS::moverJugador(int jugadorId, string mensaje){
	Jugador* jugador = this->mapJugadores[jugadorId];

	vector<string> result = splitE(mensaje, ';');

	int vecesX = atoi(result[0].c_str());
	string estado = result[1];

	list<mensajeStruct> returnList;
	jugador->mover(this->ancho,vecesX, estado);

	/*if (direccion == "DERECHA"){
		//jugador->getMovimiento()->setDirDerecha();
		jugador->mover(this->ancho,+1);

	}else if (direccion == "IZQUIERDA"){
		//jugador->getMovimiento()->setDirIzquierda();
		jugador->mover(this->ancho,-1);
	}*/

	returnList.push_back(getMensajeJugador(jugador));

	moverEscenario(&returnList);

	return returnList;
}


int EscenarioS::moverEscenario(list<mensajeStruct>* mainList){
	int minPosX;

	for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
		if (jugador->second->conectado){
			if (jugador->second->getPosX() < minPosX){
				minPosX = jugador->second->getPosX();
			}
		}
	}


	if (minPosX > this->avance){
		this->avance = minPosX;

		mainList->push_back(getMensajeEscenario());

		for (map<int,Jugador*>::iterator jugador=this->mapJugadores.begin(); jugador!=this->mapJugadores.end(); ++jugador){
			if (!jugador->second->conectado){
				if (jugador->second->getPosX() < this->avance){
					jugador->second->setPosX(this->avance);

					mainList->push_back(getMensajeJugador(jugador->second));
				}
			}
		}
	}

	return 0;
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
