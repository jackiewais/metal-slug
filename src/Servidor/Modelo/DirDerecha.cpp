#include "DirDerecha.h"
#include "Posicion.h"

DirDerecha* DirDerecha::unica_instancia = NULL;

DirDerecha::DirDerecha() : Direccion(new Posicion(1,0)) {

}

DirDerecha::~DirDerecha() {

	delete this->unica_instancia;
}


Posicion* DirDerecha::getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario) {

	Posicion* nuevaPos;
	this->direccion->setCoordenadaX(this->direccion->getCoordenadaX()*velocidad);

	nuevaPos = this->direccion->sumarPosicion(posicion);

	if (nuevaPos->getCoordenadaX() + anchoJugador > anchoEscenario) {
		nuevaPos->setCoordenadaX(anchoEscenario - anchoJugador);
	}

	return nuevaPos;
}

