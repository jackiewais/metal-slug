/*
 * ContenedorBalas.h
 *
 *  Created on: 06/11/2016
 *      Author: nahue
 */

#ifndef CONTENEDORBALAS_H_
#define CONTENEDORBALAS_H_
#include <iostream>
#include <list>
#include "LTextureBasic.h"
#include "../Common/Modelo.h"
using namespace std;

class ContenedorBalas {
public:
	LTextureBasic balasTexture;
	struct pos{
		int x;
		int y;
		weapon tipo;
	};
	list<pos> balas;
	std::string spritePath;
	int anchoFrame;
	int altoFrame;

	void initTexture(std::string spritePath, int anchoTot, int altoTot);
	bool loadMedia(SDL_Renderer* gRend);

	void addBalas(int x, int y, int tipo);
	void deleteBalas();
	void render();

	ContenedorBalas();
	virtual ~ContenedorBalas();
};


#endif /* CONTENEDORBALAS_H_ */
