#ifndef SRC_SERVIDOR_ESTADOJUGADOR_H_
#define SRC_SERVIDOR_ESTADOJUGADOR_H_

class EstadoJugador {
public:
	virtual EstadoJugador* getNuevoEstado();
	virtual ~EstadoJugador();
};

#endif /* SRC_SERVIDOR_ESTADOJUGADOR_H_ */
