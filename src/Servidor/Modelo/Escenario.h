#ifndef SRC_SERVIDOR_MODELO_ESCENARIO_H_
#define SRC_SERVIDOR_MODELO_ESCENARIO_H_
#include <stdio.h>
#include <map>
#include "Capa.h"
#include "Jugador.h"

class Escenario {

private:
	map<int, Capa*> mapCapas;
	map<int, Jugador*> mapJugadores;

public:
	Escenario(map<int, Capa*> mapCapas, map<int, Jugador*> mapJugadores);
	virtual ~Escenario();
	Capa* getCapaById(int id);
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIO_H_ */
