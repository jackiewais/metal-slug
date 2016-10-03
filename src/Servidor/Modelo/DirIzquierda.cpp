#include "DirIzquierda.h"


DirIzquierda* DirIzquierda::unica_instancia = NULL;

DirIzquierda::DirIzquierda() : Direccion(new Posicion(-1,0)) {

}

DirIzquierda::~DirIzquierda() {

	delete this->unica_instancia;
}


Posicion* DirIzquierda::getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario) {

	Posicion* nuevaPos;
	this->direccion->setCoordenadaX(this->direccion->getCoordenadaX()*velocidad);

	nuevaPos = this->direccion->sumarPosicion(posicion);

	if (nuevaPos->getCoordenadaX() < 0) {
		nuevaPos->setCoordenadaX(0);
	}

	return nuevaPos;
}
