#ifndef SRC_CLIENTE_LTEXTURE_H_
#define SRC_CLIENTE_LTEXTURE_H_

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

class Escenario;

class LTexture
{
	public:
		LTexture(Escenario *escenario, std::string path);
		~LTexture();
		bool loadFromFile();
		void free();
		void render( int x, int y, SDL_Rect *frame = NULL);
		int getWidth();
		int getHeight();
		void setWidth(int mWidth);
		void setHeight(int mHeight);
		void setPath(std::string path);
		void agregarEstado(estadoJugador estado, int anchoFrame, int altoFrame, int cantFrames, int ordenEstado);
		void setAlpha( Uint8 alpha );


		SDL_Texture* mTexture;
		map<estadoJugador, list<SDL_Rect>*> mapFrames;
	private:
		int mWidth;
		int mHeight;
		int widthScaled;
		int heightScaled;
		int anchoFrame;
		int altoFrame;
		Escenario *escenario;
		std::string path;

		SDL_Rect crearFrame(int fila, int columna, int anchoFrame, int altoFrame);
};

#endif /* SRC_CLIENTE_LTEXTURE_H_ */
