#include "Escenario.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

Escenario::Escenario() {
	this->gWindow = NULL;
	this->gRenderer = NULL;
	// Valores por defecto
	this->screenWidth = 800;
	this->screenHeight = 600;
}

Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}

bool Escenario::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void Escenario::addSprite(std::string idSprite, int ancho, int alto) {
	LTexture *textura;

	textura = new LTexture(this, "images/" + idSprite + ".png");
	this->mapTexturas[idSprite] = textura;


	if (ancho != 0)
		textura->setWidth(ancho);
	if (alto != 0)
		textura->setHeight(alto);
}

bool Escenario::loadMedia()
{
	LTexture *textura;
	std::map<std::string, LTexture*>::iterator it;

	for (it = this->mapTexturas.begin(); it != this->mapTexturas.end(); it++) {
		textura = it->second;

		if( !textura->loadFromFile() ) {
			printf( "Failed to load texture image!\n" );
			textura->free();
			// Como no se pudo cargar la imagen se carga una por defecto
			textura->setPath("images/default.png");
			if ( !textura->loadFromFile() ) {
				textura->free();
				return false;
			}
		}
	}
	return true;
}
void Escenario::moverFondo(mensajeStruct msg){

		int desplB = 0;
		int anchoA = 1000;
		int desplA = 0;
		int anchoB = 1200;
		int anchoC = 2000;
		int desplC=0;
		int offsetB=0;
		int offsetC=0;
		int posA = atoi(msg.message.c_str());
		desplA = posA;
					//DESPLC = ANCHOC - ANCHO ESCENARIO

					//DESPLD = ANCHOD - ANCHO ESCENARIO
					// EL 2 Y 3 SON LOS FACTORES DE DESPLAZMIENTO.
					// 2 = DESPC/DESPA ; 3 = DESPD/DESPLC
					// 2000 ES EL OFFSET PARA EMEPZAR EN CERO
					// 3000 ES EL OFFSET PARA EMPEZAR EN CERO

					//FACTOR AB = (anchoA+desplA-800)
					//FACTOR BC = (anchoC+desplC-800)
					//OFFSETB
					//OFFSETC
					//desplC = (FACTORAB - ANCHOC)*PARALLAX ) + OFFSETB
					offsetB = ( (anchoA- anchoB)*2)*-1;
					desplB = ( (anchoA+desplA-anchoB)*2)+offsetB;
				    offsetC = ((anchoB-anchoC)*3)*-1;
					desplC = ( (anchoB+desplB-  anchoC)*3)+offsetC;


					//Background layers
					actualizarPosicionObjeto("F02",desplA,0);
					actualizarPosicionObjeto("F03",desplB,0);
					actualizarPosicionObjeto("F04",desplC,0);

}

void calculoParallax(){





}
void Escenario::close()
{
	std::map<std::string, LTexture*>::iterator it;
	//Free loaded images
	for (it = this->mapTexturas.begin(); it != this->mapTexturas.end(); it++) {
		it->second->free();
	}
	std::map<std::string, ObjetoGraficable*>::iterator itOb;
	for (itOb = this->mapObjetosGraficables.begin(); itOb != this->mapObjetosGraficables.end(); itOb++) {
		delete itOb->second;
	}

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Escenario::getGRenderer()
{
	return this->gRenderer;
}
void Escenario::setDimensiones(int screenWidth, int screenHeight){
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void Escenario::crearObjeto(std::string idObj, std::string idSprite, int x, int y) {
	// Se comprueba que el sprite haya sido cargado antes
	if ( this->mapTexturas.find(idSprite) != this->mapTexturas.end() ) {
		LTexture *textura = this->mapTexturas[idSprite];
		this->mapObjetosGraficables[idObj] = new ObjetoGraficable(idObj, textura, x, y);
	}
}

void Escenario::renderizarObjetos() {
	SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( this->gRenderer );

	std::map<std::string, ObjetoGraficable*>::iterator it;
	for (it = this->mapObjetosGraficables.begin(); it != this->mapObjetosGraficables.end(); it++) {
		it->second->render();
	}

	SDL_RenderPresent( this->gRenderer );
}

void Escenario::actualizarPosicionObjeto(std::string idObj, int x, int y) {
	// Si el objeto esta en el map
	if ( this->mapObjetosGraficables.find(idObj) != this->mapObjetosGraficables.end() ) {
		this->mapObjetosGraficables[idObj]->actualizarPosicion(x, y);
	}
}

void Escenario::eliminarObjeto(std::string idObj) {
	// Si el objeto esta en el map
	if ( this->mapObjetosGraficables.find(idObj) != this->mapObjetosGraficables.end() ) {
		delete this->mapObjetosGraficables[idObj];
		this->mapObjetosGraficables.erase(idObj);
	}
}
