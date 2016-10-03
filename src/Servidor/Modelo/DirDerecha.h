#ifndef SRC_SERVIDOR_MODELO_DIRDERECHA_H_
#define SRC_SERVIDOR_MODELO_DIRDERECHA_H_
#include "Direccion.h"

class DirDerecha : public Direccion {
public:
	DirDerecha();
	virtual ~DirDerecha();
	Posicion* getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario);
};

#endif /* SRC_SERVIDOR_MODELO_DIRDERECHA_H_ */
