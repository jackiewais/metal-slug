#ifndef SRC_SERVIDOR_CONECTADOJUGADOR_H_
#define SRC_SERVIDOR_CONECTADOJUGADOR_H_
#include <stddef.h>
#include "EstadoJugador.h"

class ConectadoJugador : public EstadoJugador {

private:
	ConectadoJugador();
	static ConectadoJugador* unica_instancia;

public:
	EstadoJugador* getNuevoEstado();
	virtual ~ConectadoJugador();

 static ConectadoJugador* getEstado()
 {
  if(unica_instancia == NULL)
   unica_instancia = new ConectadoJugador();

  return unica_instancia;
 }
};


#endif /* SRC_SERVIDOR_CONECTADOJUGADOR_H_ */
