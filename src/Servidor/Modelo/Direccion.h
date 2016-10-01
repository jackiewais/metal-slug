#ifndef SRC_SERVIDOR_DIRECCION_H_
#define SRC_SERVIDOR_DIRECCION_H_
#include "Posicion.h"

class Direccion {

protected:
	Posicion* direccion;

public:
	Direccion(Posicion* direccion);
	virtual ~Direccion();
	Posicion* getDireccion();
};

#endif /* SRC_SERVIDOR_DIRECCION_H_ */
