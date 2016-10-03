#ifndef SRC_SERVIDOR_OBJETOMOVIBLE_H_
#define SRC_SERVIDOR_OBJETOMOVIBLE_H_
#include "Direccion.h"
#include "Posicion.h"
#include "Movimiento.h"

class ObjetoMovible {

private:
	Posicion* posicion;
	Movimiento* movimiento;

public:
	ObjetoMovible(Posicion* posicion, int ancho, int alto, int velocidad);
	virtual ~ObjetoMovible();
	Posicion* getPosicion();
	Movimiento* getMovimiento();
	void mover(int anchoEscenario);
};

#endif /* SRC_SERVIDOR_OBJETOMOVIBLE_H_ */
