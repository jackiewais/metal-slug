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
	int timer= 0;
	Enemigo(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores, string sprite);
	virtual ~Enemigo();
	virtual void mover(int anchoEscenario);
	string getStringMensajeNew();
	string getStringMensajeUpdate();
	string getCodEnemigo();
	void retrocederSegunAvanceEscenario(int avance);
	void bloquearAvanceEscenario();
	bool estaBloqueadoElAvanceDelEscenario(int anchoEscenario);
	void aparecerPorIzquierda();
	virtual bool esEnemigoFinal();
	bool restarVida(weapon arma);
	virtual string getUtimoChar();
	virtual Enemigo* lanzarEnemigo();
	void saltandoDeAvion(int x, int y);
	list<Bala*> disparar();
	list<Bala*> dispararComun();
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
	int vida;
};

#endif /* SRC_SERVIDOR_MODELO_ENEMIGO_H_ */
