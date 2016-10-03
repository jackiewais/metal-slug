#ifndef SRC_CLIENTE_LTEXTURE_H_
#define SRC_CLIENTE_LTEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Escenario.h"

class Escenario;

class LTexture
{
	public:
		LTexture(Escenario *escenario);
		~LTexture();
		bool loadFromFile( std::string path );
		void free();
		void render( int x, int y );
		int getWidth();
		int getHeight();
		void setWidth(int mWidth);
		void setHeight(int mHeight);

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
		Escenario *escenario;
};

#endif /* SRC_CLIENTE_LTEXTURE_H_ */
