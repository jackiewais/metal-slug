#ifndef SRC_SERVIDOR_POSICION_H_
#define SRC_SERVIDOR_POSICION_H_

class Posicion {

private:
	int x;
	int y;

public:
	Posicion(int x, int y);
	virtual ~Posicion();
	int getCoordenadaX();
	int getCoordenadaY();
	bool igualdadDePosicion(Posicion otraPosicion);
};

#endif /* SRC_SERVIDOR_POSICION_H_ */
