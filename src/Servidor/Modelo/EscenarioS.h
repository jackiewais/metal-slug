#ifndef SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#define SRC_SERVIDOR_MODELO_ESCENARIOS_H_
#include <stdio.h>
#include <iostream>
#include <queue>
#include <map>
#include <list>
#include "Jugador.h"
#include "Enemigo.h"
#include "../../Common/MensajeStruct.h"
#include "../../Common/Mensajeria.h"
#include "Bala.h"

class EscenarioS {

private:
	int distancia;
	int avance;
	multimap<int, Enemigo*> enemigosInactivos;
	list<Enemigo*> enemigosVivos;
	bool avanceBloqueado;

public:
	int ancho;
	int alto;
	int margen;
	map<int, Jugador*> mapJugadores;
	//BALAS
	//list<Bala> *balas;
	list<Bala*> balas;
	void addBala(list<Bala*> bala);
	void moverBala();
	EscenarioS(int ancho, int alto);
	virtual ~EscenarioS();
	Jugador* getJugadorById(int id);
	void addJugador(Jugador* jugador);
	void addEnemigoInactivo(Enemigo* enemigo, int posXAbsolutaDeJugadorParaAparicion);
	Enemigo* activarEnemigo(int posXAbsolutaJugador);
	void activarEnemigos(int posXAbsolutaJugador, list<mensajeStruct>* mainList);
	list<mensajeStruct>  moverJugador(int idJugador, string mensaje);
	void moverEscenario(list<mensajeStruct>* mainList);
	mensajeStruct getMensajeJugador(Jugador* jugador);
	mensajeStruct getMensajeEscenario();
	mensajeStruct getMensajeEnemigoNuevo(Enemigo *enemigo);
	mensajeStruct getMensajeEnemigoUpdate(Enemigo *enemigo);
	mensajeStruct getMensajeEnemigoMuerto();
	mensajeStruct getMensajeBala();
	mensajeStruct getMensajeEndOfLevel();
	void aceptarCambios();
	mensajeStruct getMensajeDesconexion(int jugadorId);
	void resetEscenario();

};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
