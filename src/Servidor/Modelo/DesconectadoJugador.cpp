#include "DesconectadoJugador.h"
#include "ConectadoJugador.h"

using namespace std;

DesconectadoJugador* DesconectadoJugador::unica_instancia = NULL;

DesconectadoJugador::DesconectadoJugador() {
	// TODO Auto-generated constructor stub
}

DesconectadoJugador::~DesconectadoJugador() {

	delete this->unica_instancia;
}


EstadoJugador* DesconectadoJugador::getNuevoEstado() {

	return ConectadoJugador::getEstado();
}
