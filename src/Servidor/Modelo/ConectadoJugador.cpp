#include "ConectadoJugador.h"
#include "DesconectadoJugador.h"

using namespace std;

ConectadoJugador* ConectadoJugador::unica_instancia = NULL;

ConectadoJugador::ConectadoJugador() {
	// TODO Auto-generated constructor stub
}

ConectadoJugador::~ConectadoJugador() {

	delete this->unica_instancia;
}


EstadoJugador* ConectadoJugador::getNuevoEstado() {

	return DesconectadoJugador::getEstado();
}
