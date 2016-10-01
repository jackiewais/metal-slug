#ifndef SRC_SERVIDOR_DESCONECTADOJUGADOR_H_
#define SRC_SERVIDOR_DESCONECTADOJUGADOR_H_
#include <stddef.h>
#include "EstadoJugador.h"

class DesconectadoJugador : public EstadoJugador {

private:
	DesconectadoJugador();
	static DesconectadoJugador* unica_instancia;

public:
	EstadoJugador* getNuevoEstado();
	virtual ~DesconectadoJugador();

 static DesconectadoJugador* getEstado()
 {
  if(unica_instancia == NULL)
   unica_instancia = new DesconectadoJugador();

  return unica_instancia;
 }
};



#endif /* SRC_SERVIDOR_DESCONECTADOJUGADOR_H_ */
