#ifndef SRC_SERVIDOR_MOVIMIENTO_H_
#define SRC_SERVIDOR_MOVIMIENTO_H_
#include "Direccion.h"
#include "Posicion.h"

class Movimiento {

private:
	int ancho;
	int alto;
	int velocidad;

public:
	Movimiento(int ancho, int alto, int velocidad);
	virtual ~Movimiento();
	Posicion* mover(Posicion* posicionActual, Direccion* direccion, int anchoEscenario);
};

#endif /* SRC_SERVIDOR_MOVIMIENTO_H_ */
