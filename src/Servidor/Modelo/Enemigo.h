#ifndef SRC_SERVIDOR_MODELO_ENEMIGO_H_
#define SRC_SERVIDOR_MODELO_ENEMIGO_H_
#include <string>
#include <iostream>
#include <map>
#include "Jugador.h"
#include "../../Common/Modelo.h"

using namespace std;

class Enemigo {
public:
	Enemigo(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores);
	virtual ~Enemigo();
	virtual void mover(int anchoEscenario);
	string getStringMensajeNew();
	string getStringMensajeUpdate();
	string getCodEnemigo();
	void retrocederSegunAvanceEscenario(int avance);
	void bloquearAvanceEscenario();
	bool estaBloqueadoElAvanceDelEscenario(int anchoEscenario);
	void aparecerPorIzquierda();

	int posX;
	int posY;
	int alto;
	int ancho;
	int velocidad;
	int velSalto;

	estadoJugador estado;
	string sprite;
protected:
	void mover(int anchoEscenario, int vecesX, string accion);
	bool estaSaltando();
	void manejarSalto();
	void moverAPosicionInicial();


	int id;
	int factorSalto = -1;
	int piso;
	int topeSalto;
	int plataforma;
	map<int, Jugador*> *mapJugadores;
	int distanciaHastaLaQueSeAcercaAJugador;
	bool avanceEscenarioBloqueado;
};

#endif /* SRC_SERVIDOR_MODELO_ENEMIGO_H_ */
