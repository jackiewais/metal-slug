#ifndef SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#define SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
#include "Capa.h"
#include "Jugador.h"
#include "../../Common/MensajeStruct.h"

class EscenarioS {

private:
	map<int, Capa*> mapCapas;
	map<int, Jugador*> mapJugadores;
	int ancho;
	int alto;

public:
	EscenarioS(int ancho, int alto, map<int, Capa*> mapCapas, map<int, Jugador*> mapJugadores);
	EscenarioS();
	virtual ~EscenarioS();
	Capa* getCapaById(int id);
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
	list<mensajeStruct>  moverJugador(int idJugador, string direccion);

};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
