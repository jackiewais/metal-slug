#ifndef SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#define SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
#include "Jugador.h"
#include "../../Common/MensajeStruct.h"
#include "../../Common/Mensajeria.h"

class EscenarioS {

private:
	int ancho;
	int alto;
	int margen;
	int distancia;
	int avance;

public:
	map<int, Jugador*> mapJugadores;

	EscenarioS(int alto, int ancho);
	virtual ~EscenarioS();
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
	list<mensajeStruct>  moverJugador(int idJugador, string mensaje);
	bool moverEscenario(list<mensajeStruct>* mainList);
	mensajeStruct getMensajeJugador(Jugador* jugador);
	mensajeStruct getMensajeEscenario();
	void aceptarCambios();
};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
