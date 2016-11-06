#include "Numero.h"
#include <iostream>

using namespace std;

void Numero::initTexture(string spritePath, int anchoTot, int altoTot)
{

	this->spritePath = spritePath;
	this->anchoFrame = anchoTot/10;
	this->altoFrame=altoTot;
	//Load media
	/*if( !loadMedia())
	{
		printf( "Failed to load media!\n" );
	}*/
}

bool Numero::loadMedia(SDL_Renderer* gRend)
{
	//Loading success flag
	bool success = true;

	gNumeroTexture.gRenderer = gRend;

	if( !gNumeroTexture.loadFromFile  ( this->spritePath ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	for (unsigned int i=0;i <= 9 ;i++){
		gSpriteClips[ i ].x =   anchoFrame * i;
		gSpriteClips[ i ].y =   0;
		gSpriteClips[ i ].w =  anchoFrame;
		gSpriteClips[ i ].h =  altoFrame;
	}

	return success;
}

void Numero::render(int id, int posX, int posY)
{
	SDL_Rect* currentClip = &gSpriteClips[ id ];
	gNumeroTexture.render( posX, posY, currentClip );
}

Numero::~Numero()
{
	gNumeroTexture.free();
}
