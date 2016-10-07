#ifndef SRC_CLIENTE_ESCENARIO_H_
#define SRC_CLIENTE_ESCENARIO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <string>
#include <map>
#include <stdio.h>
#include "ObjetoGraficable.h"

class LTexture;
class ObjetoGraficable;

class Escenario {

public:
	Escenario();
	virtual ~Escenario();
	bool init();
	void addSprite(std::string idSprite, int ancho = 0, int alto = 0);
	bool loadMedia();
	void setDimensiones(int screenWidth, int screenHeight);
	void close();
	SDL_Renderer* getGRenderer();
	void crearObjeto(std::string idObj, std::string idSprite, int x, int y);
	void renderizarObjetos();
	void actualizarPosicionObjeto(std::string idObj, int x, int y);
	void eliminarObjeto(std::string idObj);

private:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	std::map<std::string, LTexture*> mapTexturas;
	std::map<std::string, ObjetoGraficable*> mapObjetosGraficables;
	int screenWidth, screenHeight;
};

#endif /* SRC_CLIENTE_ESCENARIO_H_ */
