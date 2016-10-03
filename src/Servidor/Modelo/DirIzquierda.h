#ifndef SRC_SERVIDOR_MODELO_DIRIZQUIERDA_H_
#define SRC_SERVIDOR_MODELO_DIRIZQUIERDA_H_
#include "Direccion.h"

class DirIzquierda : public Direccion {
public:
	DirIzquierda();
	virtual ~DirIzquierda();
	Posicion* getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario);
};

#endif /* SRC_SERVIDOR_MODELO_DIRIZQUIERDA_H_ */
