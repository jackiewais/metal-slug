#ifndef SRC_SERVIDOR_MODELO_ENEMIGOHIDO_H_
#define SRC_SERVIDOR_MODELO_ENEMIGOHIDO_H_
#include <string>
#include <iostream>
#include <map>
#include "Jugador.h"
#include "Enemigo.h"

using namespace std;

class EnemigoHiDo : public Enemigo {
public:
	EnemigoHiDo(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores);
	virtual ~EnemigoHiDo();
	void mover(int anchoEscenario);
	bool esEnemigoFinal();
	string getUtimoChar();

private:
	void mover(int anchoEscenario, int vecesX);
	void moverAPosicionInicial();
};

#endif /* SRC_SERVIDOR_MODELO_ENEMIGOHIDO_H_ */
