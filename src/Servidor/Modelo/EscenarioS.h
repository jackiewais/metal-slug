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
	map<string, Enemigo*> enemigosVivos;
	bool avanceBloqueado;
	void colisionar(list<mensajeStruct>* mainList);

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
	void addEnemigoInactivo(enemigoStruct enemigoStruct);
	void matarEnemigo(list<mensajeStruct>* mainList, string id);
	void matarEnemigos(list<mensajeStruct>* mainList);
	void activarEnemigos(int posXAbsolutaJugador, list<mensajeStruct>* mainList);
	list<mensajeStruct>  moverJugador(int idJugador, string mensaje);
	void moverEscenario(list<mensajeStruct>* mainList);
	mensajeStruct getMensajeJugador(Jugador* jugador);
	mensajeStruct getMensajeEscenario();
	mensajeStruct getMensajeEnemigoNuevo(Enemigo *enemigo);
	mensajeStruct getMensajeEnemigoUpdate(Enemigo *enemigo);
	list<mensajeStruct> getMensajeBala();
	mensajeStruct getMensajeEnemigoMuerto(Enemigo *enemigo);
	mensajeStruct getMensajeEndOfLevel();
	void aceptarCambios();
	mensajeStruct getMensajeDesconexion(int jugadorId);
	void resetEscenario();
	void pasarDeNivel();
	bool endOfLevel=false;
	int nivel=1;
	int cantNiveles=3;
};

#endif /* SRC_SERVIDOR_MODELO_ESCENARIOS_H_ */
