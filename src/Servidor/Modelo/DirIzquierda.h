#ifndef SRC_SERVIDOR_MODELO_DIRIZQUIERDA_H_
#define SRC_SERVIDOR_MODELO_DIRIZQUIERDA_H_
#include "Direccion.h"
#include <stddef.h>

class DirIzquierda : public Direccion {

private:
	static DirIzquierda* unica_instancia;

public:
	DirIzquierda();
	virtual ~DirIzquierda();
	Posicion* getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario);

	static DirIzquierda* getDireccion() {
		  if(unica_instancia == NULL)
		   unica_instancia = new DirIzquierda();

		  return unica_instancia;
		 }
};

#endif /* SRC_SERVIDOR_MODELO_DIRIZQUIERDA_H_ */
