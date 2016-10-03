#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>
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
	Jugador(int id, Posicion* posicon, int ancho, int alto, int velocidad);
	virtual ~Jugador();
	int getId();
	EstadoJugador* getEstado();
	void cambiarEstado();
	string getPosConcat();
	//void interceptarA(Capa* capa);
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
