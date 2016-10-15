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
	int distancia;
	int avance;

public:
	int margen;
	map<int, Jugador*> mapJugadores;

	EscenarioS(int ancho, int alto);
	virtual ~EscenarioS();
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
	list<mensajeStruct>  moverJugador(int idJugador, string mensaje);
	void moverEscenario(list<mensajeStruct>* mainList);
	mensajeStruct getMensajeJugador(Jugador* jugador);
	mensajeStruct getMensajeEscenario();
	void aceptarCambios();
	mensajeStruct getMensajeDesconexion(int jugadorId);
};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
