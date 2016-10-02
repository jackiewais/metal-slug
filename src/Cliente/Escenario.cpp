#include "Escenario.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


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

bool Escenario::loadMedia()
{
	// Esto esta harcodeado, me tendrian que pasar algun tipo de lista o array
	std::string idsSprints[] = {"foo", "primerFondo"};
	LTexture *textura;
	//this->mapTexturas["background"] = new LTexture(this);

	bool success = true;

	for (unsigned int i=0; i < (sizeof((idsSprints))/sizeof((idsSprints[0]))); i++) {
		textura = new LTexture(this);
		if( !textura->loadFromFile( "images/" + idsSprints[i] + ".png" ) )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
			textura->free();
		} else {
			this->mapTexturas[idsSprints[i]] = textura;
		}
	}

	return success;
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

bool Escenario::crearEscenario(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	if (this->init()) {
		if (this->loadMedia())
			return true;
	}
	return false;
}

void Escenario::crearObjeto(std::string idObj, std::string idSprite, int x, int y) {
	LTexture *textura = this->mapTexturas[idSprite];
	this->mapObjetosGraficables[idObj] = new ObjetoGraficable(idObj, textura, x, y);
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
	this->mapObjetosGraficables[idObj]->actualizarPosicion(x, y);
}

void Escenario::eliminarObjeto(std::string idObj) {
	delete this->mapObjetosGraficables[idObj];
	this->mapObjetosGraficables.erase(idObj);
}
