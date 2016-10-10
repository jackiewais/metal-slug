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
	int getAncho();
	void setFactorParallax(int despA, int anchoVentana);
	void actualizarPosicionFondo(int despA);

private:
	std::string id;
	LTexture *textura;
	int x, y, factorParallax;
};

#endif /* SRC_CLIENTE_OBJETOGRAFICABLE_H_ */
