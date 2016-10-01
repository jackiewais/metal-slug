#ifndef SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#define SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#include <stdio.h>
#include <map>
#include "Capa.h"
#include "Jugador.h"

class EscenarioS {

private:
	map<int, Capa*> mapCapas;
	map<int, Jugador*> mapJugadores;

public:
	EscenarioS(map<int, Capa*> mapCapas, map<int, Jugador*> mapJugadores);
	virtual ~EscenarioS();
	Capa* getCapaById(int id);
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
