#include "Capa.h"

Capa::Capa(int id, Posicion* posicion) : ObjetoMovible(posicion) {

	this->id = id;
}

Capa::~Capa() {
	// TODO Auto-generated destructor stub
}



int Capa::getId() {

	return this->id;
}


//void Capa::interceptarA(ConectadoJugador* conectado, Jugador* jugador) {

	//logica para avanzar si es en el limite derecho del escenario y si no hay otro jugador conectado que lo impida.
	//o sea, que se encuentre en el limite izquierdo del escenario.
//}


//void Capa::interceptarA(DesconectadoJugador* desconectado, Jugador* jugador) {

	//no hacer nada.
	//se supone que esta el jugador grisado en el limite izquierdo del escenario, entonces no se mueve(seria como que se va arrastrando)
//}

