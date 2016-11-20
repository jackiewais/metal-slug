#ifndef GRAFICABLEB_H_
#define GRAFICABLEB_H_


#include "LTextureBasic.h"

class GraficableBasic
{
	public:
	void initTexture(std::string spritePath, int anchoTot, int altoTot, int id=1);
	void render(int posX, int posY, int id=1);

	bool loadMedia(SDL_Renderer* gRend);

	void close();
	~GraficableBasic();

	LTextureBasic gTexture;

	std::string spritePath;

	int anchoTot;
	int altoTot;
	int cantFrames;
	SDL_Rect* gSpriteClips;

};

#endif
