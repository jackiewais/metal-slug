/*
 * ContenedorBalas.cpp
 *
 *  Created on: 06/11/2016
 *      Author: nahue
 */

#include "ContenedorBalas.h"



ContenedorBalas::ContenedorBalas() {
	// TODO Auto-generated constructor stub

}

ContenedorBalas::~ContenedorBalas() {
	// TODO Auto-generated destructor stub
}

void ContenedorBalas::addBalas(int x, int y){

	pos posicion;
	posicion.x = x;
	posicion.y = y;

	this->balas.push_front(posicion);

}
void ContenedorBalas::initTexture(std::string spritePath, int anchoTot, int altoTot){
	this-> spritePath = spritePath;
	this-> anchoFrame = anchoTot;
	this-> altoFrame = altoFrame;
}

bool ContenedorBalas::loadMedia(SDL_Renderer* gRend)
{
	//Loading success flag
	bool success = true;

	this->balasTexture.gRenderer = gRend;

	if( !balasTexture.loadFromFile( this->spritePath ) )
	{
		printf( "Failed to load texture!\n" );
		success = false;
	}

	return success;
}
void ContenedorBalas::render()
{
	list<pos>::iterator it;
		for (it=balas.begin(); it!=balas.end(); ++it){

			int posX=(*it).x;
			int posY=(*it).y;
			this->balasTexture.render( posX, posY, 0 );
		}
}

//sin usar por ahora.
void ContenedorBalas::deleteBalas(){
	list<pos>::iterator it;
		for (it=balas.begin(); it!=balas.end(); ++it){
			balas.pop_front();
		}
}
