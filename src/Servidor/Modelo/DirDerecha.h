#ifndef SRC_SERVIDOR_MODELO_DIRDERECHA_H_
#define SRC_SERVIDOR_MODELO_DIRDERECHA_H_
#include "Direccion.h"
#include <stddef.h>

class DirDerecha : public Direccion {

private:
	static DirDerecha* unica_instancia;

public:
	DirDerecha();
	virtual ~DirDerecha();
	Posicion* getSiguientePosicion(Posicion* posicion, int velocidad, int anchoJugador, int anchoEscenario);

	static DirDerecha* getDireccion() {
	  if(unica_instancia == NULL)
	   unica_instancia = new DirDerecha();

	  return unica_instancia;
	 }
};

#endif /* SRC_SERVIDOR_MODELO_DIRDERECHA_H_ */
