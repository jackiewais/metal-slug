#ifndef NUMERO_H_
#define NUMERO_H_


#include "LTextureBasic.h"

class Numero
{
	public:
	void initTexture(std::string spritePath, int anchoTot, int altoTot);
	void render(int id, int posX, int posY);

	void close();
	bool loadMedia(SDL_Renderer* gRend);

	~Numero();

	LTextureBasic gNumeroTexture;
	LTextureBasic gInfinitoTexture;

	std::string spritePath;

	int anchoFrame;
	int altoFrame;

	SDL_Rect gSpriteClips[ 10 ];
};

#endif
