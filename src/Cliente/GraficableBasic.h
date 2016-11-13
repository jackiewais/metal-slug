#ifndef GRAFICABLEB_H_
#define GRAFICABLEB_H_


#include "LTextureBasic.h"

class GraficableBasic
{
	public:
	void initTexture(SDL_Renderer* gRend, std::string spritePath, int anchoTot, int altoTot);
	void render(int posX, int posY);

	bool loadMedia();

	void close();
	~GraficableBasic();

	LTextureBasic gTexture;

	std::string spritePath;

	int anchoTot;
	int altoTot;
	SDL_Rect currentClip;


};

#endif
