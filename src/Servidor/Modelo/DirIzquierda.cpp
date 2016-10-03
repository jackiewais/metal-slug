#include "DirIzquierda.h"

DirIzquierda::DirIzquierda() : Direccion(new Posicion(-1,0)) {
	// TODO Auto-generated constructor stub

}

DirIzquierda::~DirIzquierda() {
	// TODO Auto-generated destructor stub
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
