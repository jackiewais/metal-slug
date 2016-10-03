#ifndef SRC_SERVIDOR_POSICION_H_
#define SRC_SERVIDOR_POSICION_H_
#include <string>

using namespace std;

class Posicion {

private:
	int x;
	int y;

public:
	Posicion(int x, int y);
	virtual ~Posicion();
	int getCoordenadaX();
	void setCoordenadaX(int x);
	int getCoordenadaY();
	void setCoordenadaY(int Y);
	bool igualdadDePosicion(Posicion* otraPosicion);
	Posicion* sumarPosicion(Posicion* otraPosicion);
	string getPosConcat();
};

#endif /* SRC_SERVIDOR_POSICION_H_ */
