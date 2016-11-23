#include "GraficableBasic.h"
#include <iostream>

using namespace std;

void GraficableBasic::initTexture(string spritePath, int anchoTot, int altoTot, int cantFrames)
{

	this->spritePath = spritePath;
	this->anchoTot = anchoTot/cantFrames;
	this->altoTot=altoTot;
	this->cantFrames = cantFrames;
	//this->gSpriteClips= SDL_Rect[cantFrames];

}

bool GraficableBasic::loadMedia(SDL_Renderer* gRend)
{
	//Loading success flag
	bool success = true;
	gTexture.gRenderer = gRend;
	if( !gTexture.loadFromFile  ( "images/" + this->spritePath+ ".png" ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	for (int i=0;i < cantFrames ;i++){
		gSpriteClips[ i ].x =   anchoTot * i;
		gSpriteClips[ i ].y =   0;
		gSpriteClips[ i ].w =  anchoTot;
		gSpriteClips[ i ].h =  altoTot;
	}

	return success;
}


void GraficableBasic::render(int posX, int posY, int id)
{
	SDL_Rect currentClip = gSpriteClips[id-1];
	gTexture.render( posX, posY, &currentClip );
}

void GraficableBasic::close(){

	gTexture.free();
}

GraficableBasic::~GraficableBasic()
{
	close();
}
