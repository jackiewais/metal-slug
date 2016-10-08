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
		LTexture(Escenario *escenario, std::string path);
		~LTexture();
		bool loadFromFile();
		void free();
		void render( int x, int y );
		int getWidth();
		int getHeight();
		void setWidth(int mWidth);
		void setHeight(int mHeight);
		void setPath(std::string path);

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
		Escenario *escenario;
		std::string path;
};

#endif /* SRC_CLIENTE_LTEXTURE_H_ */
