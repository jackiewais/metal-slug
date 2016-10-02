#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>
#include "ObjetoMovible.h"
#include "Posicion.h"
#include "Capa.h"
#include "EstadoJugador.h"

using namespace std;

class Jugador : public ObjetoMovible {

private:
	int id;
	string nombre;
	int puntaje;
	EstadoJugador* estado;

	int posX;
	int posY;
	int velocidad = 10;
	int ancho;
	int alto;
	int anchoEscenario;

public:
	Jugador(int id, Posicion* posicon);
	virtual ~Jugador();
	int getId();
	EstadoJugador* getEstado();
	void cambiarEstado();
	void moverDerecha();
	void moverIzquierda();
	string getPosConcat();
//	void interceptarA(Capa* capa);
//	void interceptarA(Jugador* jugador);
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
