#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>
/*#include "ObjetoMovible.h"
#include "Posicion.h"*/
#include "Capa.h"

using namespace std;

class Jugador /*: public ObjetoMovible*/ {

private:
	int id;
	string nombre;
	int puntaje;


public:
	bool conectado;
	int posX;
	int posY;
	string estado;
	int alto;
	int ancho;
	int velocidad;

	Jugador(int id, int velocidad);
	virtual ~Jugador();
	int getId();
	void mover(int anchoEscenario, int vecesX);
	string getPosConcat();
	string getCodJugador();
	int getPosX();
	void setPosX(int x);
	int getPosY();
	void setPosY(int y);
};

#endif /* SRC_SERVIDOR_JUGADOR_H_ */
