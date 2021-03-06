#ifndef SRC_CLIENTE_ESCENARIO_H_
#define SRC_CLIENTE_ESCENARIO_H_

#include "../Common/MensajeStruct.h"
#include "../Common/Modelo.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "LTextureBasic.h"
#include <string>
#include <map>
#include <stdio.h>
#include "ObjetoGraficable.h"
#include "Numero.h"
#include "Contador.h"
#include "Progreso.h"
#include "ContenedorBalas.h"
#include "GraficableBasic.h"
#include "Bonus.h"

class LTexture;
class ObjetoGraficable;

class Escenario {

public:
	Escenario();
	virtual ~Escenario();
	bool init();
	LTexture* addSprite(std::string idSprite, int ancho = 0, int alto = 0);
	void addGraficableBasic(string id, string sprite, int ancho, int alto, int frames);
	bool loadMedia();
	void setDimensiones(int screenWidth, int screenHeight);
	void close();
	SDL_Renderer* getGRenderer();
	void crearObjeto(std::string idObj, std::string idSprite, int x, int y, estadoJugador estado, std::string conectado);
	void renderizarObjetos();
	void actualizarPosicionObjeto(std::string idObj, int x, int y, estadoJugador estado, std::string conectado);
	void eliminarObjeto(std::string idObj);
	void moverFondo(mensajeStruct msg);
	void addFondo(std::string objectId);
	void calcularParallax();
	void agregarEstado(std::string idSprite, estadoJugador estado, int anchoFrame, int altoFrame, int cantFrames, int ordenEstado);
	void crearJugadorPrincipal(mensajeStruct msg);
	bool running = false;
	bool esperandoJugadores=false;
	void renderPausa();
	void actualizarEnemigo(std::string idObj, int x, int y);
	ContenedorBalas balas;
	Numero* numero;
	Progreso* progreso;
	Label* lbalas;
	//GraficableBasic* iGameOver;
	//GraficableBasic* iFondoNegro;
	std::map<std::string,Contador*> contadores;
	std::map<int,Bonus*> bonuses;
	Numero* crearNumero(std::string idSprite, int ancho, int alto  );
	Progreso* crearProgreso(std::string idSprite, int ancho, int alto  );
	Contador* crearContador(std::string id, int puntaje, int vida, int municiones);
	bool isGameOver();

	void crearBonus(int id, int x, int y, bonusTypes bonus);
	void updateBonus(int id, int x, int y, bonusTypes bonus);
	void deleteBonus(int id);
	void creaBala(mensajeStruct mesajeRta);
	bool gameOver=false;
	bool gameOverAll=false;
	bool endOfLevel=false;
	Label* lGameOver;
	void setGameOverMe();
	void setGameOverAll();
	std::list<Label*> eoLevelLabels;
	void addEOLevelLabel(string name, int posX, int posY);
	void loadMediaEOLevelLabels();
private:
	void cargarMensajeEsperandoJugador();
	ObjetoGraficable *esperandoJugador;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	std::map<std::string, LTexture*> mapTexturas;
	std::map<std::string, ObjetoGraficable*> mapObjetosGraficables;
	std::map<std::string, ObjetoGraficable*> mapFondos;
	std::map<std::string, GraficableBasic*> graficablesBasic;
	ObjetoGraficable *jugadorPrincipal;
	int screenWidth, screenHeight;
	int fondoMasChico = 0 ; // para el calculo de parallax.
	bool faltaHacerLoadMediaEOLevelLabels;

};

#endif /* SRC_CLIENTE_ESCENARIO_H_ */
