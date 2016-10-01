#ifndef SRC_SERVIDOR_MOVIMIENTO_H_
#define SRC_SERVIDOR_MOVIMIENTO_H_
#include "Direccion.h"
#include "Posicion.h"

class Movimiento {

private:
	Direccion* direccion;

public:
	Movimiento();
	virtual ~Movimiento();
	void setDireccion(Direccion* direccion);
	Posicion* avanzar(Posicion* posicionActual);
};

#endif /* SRC_SERVIDOR_MOVIMIENTO_H_ */
