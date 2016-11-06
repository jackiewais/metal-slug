#include "Progreso.h"
#include <iostream>

using namespace std;

void Progreso::initTexture(string spritePath, int anchoTot, int altoTot)
{

	this->spritePath = spritePath;
	this->anchoTot = anchoTot;
	this->altoTot=altoTot;
	//Load media
	/*if( !loadMedia())
	{
		printf( "Failed to load media!\n" );
	}*/
}

bool Progreso::loadMedia(SDL_Renderer* gRend)
{
	//Loading success flag
	bool success = true;

	gTexture.gRenderer = gRend;

	if( !gTexture.loadFromFile  ( this->spritePath ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	loadMediaBase();

	return success;
}

bool Progreso::loadMediaBase()
{
	//Loading success flag
	bool success = true;

	gTextureBase.gRenderer = gTexture.gRenderer;

	if( !gTextureBase.loadFromFile  ( this->spritePath ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	this->gTextureBase.setAlpha(64);

	return success;
}

void Progreso::render(int porcentaje, int posX, int posY)
{

	currentClip.x = 0;
	currentClip.y = 0;
	currentClip.h = altoTot;
	currentClip.w = anchoTot;
	gTextureBase.render( posX, posY, &currentClip );

	currentClip.w = porcentaje;
	gTexture.render( posX, posY, &currentClip );

}

Progreso::~Progreso()
{
	gTexture.free();
}
