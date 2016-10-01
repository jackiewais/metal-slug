#ifndef SRC_CLIENTE_OBJETOGRAFICABLE_H_
#define SRC_CLIENTE_OBJETOGRAFICABLE_H_

#include <string>
#include "Escenario.h"
#include "LTexture.h"

class LTexture;

class ObjetoGraficable {
public:
	ObjetoGraficable(std::string id, LTexture *textura, int x, int y);
	virtual ~ObjetoGraficable();
	void actualizarPosicion(int x, int y);
	void render();

private:
	std::string id;
	LTexture *textura;
	int x, y;
};

#endif /* SRC_CLIENTE_OBJETOGRAFICABLE_H_ */
