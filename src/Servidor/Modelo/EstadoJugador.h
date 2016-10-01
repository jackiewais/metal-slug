#ifndef SRC_SERVIDOR_ESTADOJUGADOR_H_
#define SRC_SERVIDOR_ESTADOJUGADOR_H_

class EstadoJugador {

protected:
	 EstadoJugador();
	 virtual ~EstadoJugador();

public:
	virtual EstadoJugador* getNuevoEstado();
};

#endif /* SRC_SERVIDOR_ESTADOJUGADOR_H_ */
