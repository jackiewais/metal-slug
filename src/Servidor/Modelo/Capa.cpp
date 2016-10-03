#include "Capa.h"

Capa::Capa(int id, Posicion* posicion, int ancho, int alto, int velocidad) : ObjetoMovible(posicion,ancho,alto,velocidad) {

	this->id = id;
}

Capa::~Capa() {
	// TODO Auto-generated destructor stub
}



int Capa::getId() {

	return this->id;
}

