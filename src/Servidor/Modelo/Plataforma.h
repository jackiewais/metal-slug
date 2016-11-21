/*
 * Plataforma.h

 *
 *  Created on: 06/11/2016
 *      Author: silvia
 */
#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_
#include <string>
#include <iostream>
#include "Jugador.h"
#include <map>
#include "../../Common/Modelo.h"

using namespace std;

class Plataforma {
public:
	Plataforma(int id,string imagen, int velocidad, int posXP, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores);
	void mover(int anchoEscenario, int vecesX, string accion);
	void mover(int anchoEscenario);
	string getCodPlataforma();
	void retrocederSegunAvanceEscenario(int avance);
	string getStringMensajeUpdate();
	string getStringMensajeNew();
	void bloquearAvanceEscenario();
	int getPosX();
	int getAncho();
	int getPiso();
	bool estaBloqueadoElAvanceDelEscenario(int anchoEscenario);

	int ancho;
	int alto;
	int posX;
	int posY;
	int velocidad;
	string imagen;
	estadoJugador estado;


	~Plataforma();

	private:
	int id;
	map<int, Jugador*> *mapJugadores;
	int piso;
	bool avanceEscenarioBloqueado;
	int distanciaHastaLaQueSeAcercaAJugador;


	void moverAPosicionInicial();
};

#endif




