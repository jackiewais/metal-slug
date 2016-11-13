#include "GraficableBasic.h"
#include <iostream>

using namespace std;

void GraficableBasic::initTexture(SDL_Renderer* gRend, string spritePath, int anchoTot, int altoTot)
{

	this->spritePath = spritePath;
	this->anchoTot = anchoTot;
	this->altoTot=altoTot;

	gTexture.gRenderer = gRend;
	//Load media
	if( !loadMedia())
	{
		printf( "Failed to load media!\n" );
	}
}

bool GraficableBasic::loadMedia()
{
	//Loading success flag
	bool success = true;

	if( !gTexture.loadFromFile  ( "images/" + this->spritePath+ ".png" ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	return success;
}


void GraficableBasic::render(int posX, int posY)
{
	currentClip.x = 0;
	currentClip.y = 0;
	currentClip.h = altoTot;
	currentClip.w = anchoTot;
	gTexture.render( posX, posY, &currentClip );

}

void GraficableBasic::close(){

	gTexture.free();
}

GraficableBasic::~GraficableBasic()
{
}
