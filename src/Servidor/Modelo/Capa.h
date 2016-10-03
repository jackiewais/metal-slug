#ifndef SRC_SERVIDOR_MODELO_CAPA_H_
#define SRC_SERVIDOR_MODELO_CAPA_H_
#include "ObjetoMovible.h"
#include "Posicion.h"
#include "Jugador.h"

class Capa : public ObjetoMovible {

private:
	int id;

public:
	Capa(int id, Posicion* posicion, int ancho, int alto, int velocidad);
	virtual ~Capa();
	int getId();
};

#endif /* SRC_SERVIDOR_MODELO_CAPA_H_ */
