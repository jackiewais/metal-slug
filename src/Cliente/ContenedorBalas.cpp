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

void ContenedorBalas::addBalas(int x, int y, int tipo,aimDirection direccion){

	pos posicion;
	posicion.direccion = direccion;
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
	int offset;
	bool up= false;
	int offsetMachine = 0;
	SDL_RendererFlip flip;
	list<pos>::iterator it;
		for (it=balas.begin(); it!=balas.end(); ++it){
			int posX=(*it).x;
			int posY=(*it).y;
			double angulo = 0;
			switch (it->direccion){
			case RIGHT:
				offset=0;
				offsetMachine = 0;
				flip = SDL_FLIP_NONE;
				break;
			case LEFT:
				flip = SDL_FLIP_HORIZONTAL;
				offsetMachine = 80;
				offset = 80;
				break;
			case UP:
				flip = SDL_FLIP_NONE;
				angulo = 0;
				offsetMachine = 160;
				up = true;
				break;
			case DIAGLEFT:
				angulo = 45;
				offsetMachine = 290;
				break;
			case DIAGRIGHT:
				offsetMachine = 220;
				angulo = 135;
				break;
			}

		switch (it->tipo){

		case MACHINEGUN:
		currentClip.x = offsetMachine;
		currentClip.y = 50;
		currentClip.h = 150;
		currentClip.w = 70;
		flip = SDL_FLIP_NONE;
		angulo = 0;
		break;
		case SHOOTGUN:
			if(up==true){
			angulo =270;
		}
		currentClip.x = 0;
		currentClip.y = 200;
		currentClip.h = 100;
		currentClip.w = 85;
		for(int i =0 ; i<5 ; i++){
			for (int j= 0; j <4 ; j++){

			this->balasTexture.render( posX, posY, &currentClip,angulo,NULL,flip );
			currentClip.x +=99;
			}
			currentClip.y+=80;
		}
		break;
		case GUN:

		currentClip.x = 0;
		currentClip.y = 0;
		currentClip.h = 50;
		currentClip.w = 30;
		break;
		case TANIOHGUN:
		currentClip.x = 0;
		currentClip.y = 450;
		currentClip.h = 50;
		currentClip.w = 50;
		break;
		case BOMB:
			currentClip.x = 0;
			currentClip.y = 525;
			currentClip.h = 70;
			currentClip.w = 50;
			//for(int i =0 ; i<5 ; i++){
			//this->balasTexture.render( posX, posY, &currentClip);
			//currentClip.x +=50;

			//}

		}


		this->balasTexture.render( posX, posY, &currentClip,angulo,NULL,flip);
		}

}

//sin usar por ahora.
void ContenedorBalas::deleteBalas(){
	list<pos>::iterator it;
		for (it=balas.begin(); it!=balas.end(); ++it){
			balas.pop_front();
		}
}
