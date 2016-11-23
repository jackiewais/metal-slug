#ifndef SRC_SERVIDOR_MODELO_ENEMIGOAIRBUSTERRIBERTS_H_
#define SRC_SERVIDOR_MODELO_ENEMIGOAIRBUSTERRIBERTS_H_
#include <string>
#include <iostream>
#include <map>
#include "Jugador.h"
#include "Enemigo.h"

using namespace std;

class EnemigoAirbusterRiberts : public Enemigo {
public:
	EnemigoAirbusterRiberts(int id, int velocidad, int ancho, int alto, int altoEscenario, map<int, Jugador*> *mapJugadores);
	virtual ~EnemigoAirbusterRiberts();
	void mover(int anchoEscenario);
	bool esEnemigoFinal();
	string getUtimoChar();

private:
	void mover(int anchoEscenario, int vecesX);
	void moverAPosicionInicial();
};

#endif /* SRC_SERVIDOR_MODELO_ENEMIGOAIRBUSTERRIBERTS_H_ */
