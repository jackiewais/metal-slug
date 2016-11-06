#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Escenario.h"
#include <iostream>
#include <list>
#include <string>
#include <map>
#include "../Common/Modelo.h"

using namespace std;

LTexture::LTexture(Escenario *escenario, std::string path)
{
	//Initialize
	this->mTexture = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
	this->widthScaled = 0;
	this->heightScaled = 0;
	this->escenario = escenario;
	this->path = path;
	this->anchoFrame = 0;
	this->altoFrame = 0;

	/*int anchoFrame = 37;
	int altoFrame = 49;*/
}

void LTexture::agregarEstado(estadoJugador estado, int anchoFrame, int altoFrame, int cantFrames, int ordenEstado) {
	list<SDL_Rect>* pList = new list<SDL_Rect>;
	this->mapFrames[estado] = pList;
	for(int i=1; i<=cantFrames; i++) {
		pList->push_back(this->crearFrame(ordenEstado, i, anchoFrame, altoFrame));
	}
	if (this->mapFrames.size() == 1) {
		/*this->itEstado = pList->begin();
		this->iteradorDeItEstado = 0;
		this->estadoActual = estado;*/
		this->anchoFrame = anchoFrame;
		this->altoFrame = altoFrame;
	}
}

SDL_Rect LTexture::crearFrame(int fila, int columna, int anchoFrame, int altoFrame) {
	int v = (columna - 1)*anchoFrame;
	int w = (fila - 1)*altoFrame;
	SDL_Rect frame = { v, w, anchoFrame, altoFrame };
	return frame;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile()
{
	//Get rid of preexisting texture
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( this->path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", this->path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( this->escenario->getGRenderer(), loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", this->path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	map<estadoJugador, list<SDL_Rect>*>::iterator it;
	//Free texture if it exists
	if( mTexture != NULL ) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		for(it = this->mapFrames.begin(); it != this->mapFrames.end(); it++) {
			delete it->second;
		}
	}
}

void LTexture::render( int x, int y, SDL_Rect *frame)
{
	int anchoRender = this->getWidth();
	int altoRender = this->getHeight();

	if (frame == NULL) {
		SDL_Rect frameDefault = { 0, 0, this->mWidth, this->mHeight };
		frame = &frameDefault;
	} else {
		if (this->widthScaled == 0) {
			anchoRender = this->anchoFrame;
		}
		if (this->heightScaled == 0) {
			altoRender = this->altoFrame;
		}
	}

	SDL_Rect renderQuad = { x, y, anchoRender, altoRender };
	SDL_RenderCopy( this->escenario->getGRenderer(), mTexture, frame, &renderQuad );
}

int LTexture::getWidth()
{
	if (this->widthScaled == 0) {
		return this->mWidth;
	}
	return this->widthScaled;
}

int LTexture::getHeight()
{
	if (this->heightScaled == 0) {
		return this->mHeight;
	}
	return this->heightScaled;
}

void LTexture::setWidth(int mWidth)
{
	this->widthScaled = mWidth;
}

void LTexture::setHeight(int mHeight)
{
	this->heightScaled = mHeight;
}

void LTexture::setPath(std::string path)
{
	this->path = path;
}

void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
