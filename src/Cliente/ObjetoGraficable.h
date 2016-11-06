#ifndef SRC_CLIENTE_OBJETOGRAFICABLE_H_
#define SRC_CLIENTE_OBJETOGRAFICABLE_H_

#include <string>
#include "Escenario.h"
#include "LTexture.h"
#include <list>

using namespace std;

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
	void setGrisado(bool grisa);
	void actualizarEstado(estadoJugador estado);
	void actualizarGrisado();

	bool grisado = false;
	int tipoObjeto = 0;
	std::string id;

private:

	LTexture *textura;
	int x, y;
	int factorParallax=0;
	int posMozaico = 0;
	bool flagGrisado = false;

	list<SDL_Rect>::iterator itEstado;
	int iteradorDeItEstado;
	estadoJugador estadoActual;
};

#endif /* SRC_CLIENTE_OBJETOGRAFICABLE_H_ */
