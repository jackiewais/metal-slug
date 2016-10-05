#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>
#include "ObjetoMovible.h"
#include "Posicion.h"
#include "Capa.h"

using namespace std;

class Jugador : public ObjetoMovible {

private:
	int id;
	string nombre;
	int puntaje;


public:
	bool conectado;

	Jugador(int id, Posicion* posicon, int ancho, int alto, int velocidad);
	virtual ~Jugador();
	int getId();
	string getPosConcat();
	string getCodJugador();
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
