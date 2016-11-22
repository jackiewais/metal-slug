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

void ContenedorBalas::addBalas(int x, int y, int tipo){

	pos posicion;
	posicion.x = x;
	posicion.y = y;
	posicion.tipo = weapon(tipo);
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
	SDL_Rect currentClip;
	list<pos>::iterator it;
		for (it=balas.begin(); it!=balas.end(); ++it){

		if(it->tipo == MACHINEGUN){
			cout << "ES MACHINE " << endl;
			currentClip.x = 0;
			currentClip.y = 50;
			currentClip.h = 50;
			currentClip.w = 70;

		}else if (it->tipo == SHOOTGUN){
				cout << "ES SHOOTGUN " << endl;
				currentClip.x = 0;
				currentClip.y = 0;
				currentClip.h = 100;
				currentClip.w = 100;

			  }else {
					cout << "ES BALA COMUN " << endl;
					currentClip.x = 0;
					currentClip.y = 0;
					currentClip.h = 50;
					currentClip.w = 30;

			  }
			int posX=(*it).x;
			int posY=(*it).y;
			this->balasTexture.render( posX, posY, &currentClip );
		}
}

//sin usar por ahora.
void ContenedorBalas::deleteBalas(){
	list<pos>::iterator it;
		for (it=balas.begin(); it!=balas.end(); ++it){
			balas.pop_front();
		}
}
