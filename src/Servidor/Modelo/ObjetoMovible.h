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
	ObjetoMovible(Posicion* posicion);
	virtual ~ObjetoMovible();
	void setDireccion(Direccion* nuevaDireccion);
	Posicion* getPosicion();
	void avanzar();
};

#endif /* SRC_SERVIDOR_OBJETOMOVIBLE_H_ */
