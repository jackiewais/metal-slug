#ifndef SRC_SERVIDOR_MODELO_CAPA_H_
#define SRC_SERVIDOR_MODELO_CAPA_H_
#include "ObjetoMovible.h"
#include "Posicion.h"
#include "ConectadoJugador.h"
#include "DesconectadoJugador.h"
#include "Jugador.h"

class Capa : public ObjetoMovible {

private:
	int id;

public:
	Capa(int id, Posicion* posicion);
	virtual ~Capa();
	int getId();
//	void interceptarA(ConectadoJugador* conectado, Jugador* jugador);
//	void interceptarA(DesconectadoJugador* desconectado, Jugador* jugador);
};

#endif /* SRC_SERVIDOR_MODELO_CAPA_H_ */
