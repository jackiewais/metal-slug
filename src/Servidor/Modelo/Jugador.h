#ifndef SRC_SERVIDOR_JUGADOR_H_
#define SRC_SERVIDOR_JUGADOR_H_
#include <string>
#include <iostream>

using namespace std;

class Jugador{

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

	Jugador(int id, int velocidad, int posX, int posY, int ancho, int alto);
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
