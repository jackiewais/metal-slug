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

	gInfinitoTexture.gRenderer = gRend;

	if( !gInfinitoTexture.loadFromFile  ( "images/infinity.png" ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	return success;
}

void Numero::render(int id, int posX, int posY)
{
	if (id==-1){
		SDL_Rect currentClip;
		currentClip.x = 0;
		currentClip.y = 0;
		currentClip.h = 25;
		currentClip.w = 61;
		gInfinitoTexture.render( posX+4, posY+2, &currentClip );
	}else{
		SDL_Rect* currentClip = &gSpriteClips[ id ];
		gNumeroTexture.render( posX, posY, currentClip );
	}
}

void Numero::close(){
	gNumeroTexture.free();

}

Numero::~Numero()
{
}
