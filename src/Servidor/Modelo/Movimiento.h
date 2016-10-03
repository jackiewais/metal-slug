#ifndef SRC_SERVIDOR_MOVIMIENTO_H_
#define SRC_SERVIDOR_MOVIMIENTO_H_
#include "Direccion.h"
#include "Posicion.h"

class Movimiento {

private:
	Direccion* direccion;
	int ancho;
	int alto;
	int velocidad;

public:
	Movimiento(int ancho, int alto, int velocidad);
	virtual ~Movimiento();
	void setDirDerecha();
	void setDirIzquierda();
	Posicion* mover(Posicion* posicionActual, int anchoEscenario);
};

#endif /* SRC_SERVIDOR_MOVIMIENTO_H_ */
