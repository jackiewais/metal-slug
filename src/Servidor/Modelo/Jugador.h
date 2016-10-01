#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include "ObjetoMovible.h"
#include "Posicion.h"
#include "Capa.h"
#include "EstadoJugador.h"

using namespace std;

class Jugador : public ObjetoMovible {

private:
	int id;
	string nombre;
	int puntaje;
	EstadoJugador* estado;

public:
	Jugador(int id, Posicion* posicon);
	virtual ~Jugador();
	int getId();
	EstadoJugador* getEstado();
	void cambiarEstado();
//	void interceptarA(Capa* capa);
//	void interceptarA(Jugador* jugador);
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
