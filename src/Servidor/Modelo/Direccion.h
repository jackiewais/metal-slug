#ifndef SRC_SERVIDOR_DIRECCION_H_
#define SRC_SERVIDOR_DIRECCION_H_
#include "Posicion.h"

class Direccion {

protected:
	Posicion* direccion;
	Direccion(Posicion* direccion);

public:
	virtual ~Direccion();
	virtual Posicion* getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario);

};

#endif /* SRC_SERVIDOR_DIRECCION_H_ */
