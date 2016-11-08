#ifndef PROGRESO_H_
#define PROGRESO_H_


#include "LTextureBasic.h"

class Progreso
{
	public:
	void initTexture(std::string spritePath, int anchoTot, int altoTot);
	void render(int id, int posX, int posY);

	bool loadMedia(SDL_Renderer* gRend);
	bool loadMediaBase();

	void close();
	~Progreso();

	LTextureBasic gTexture;
	LTextureBasic gTextureBase;

	std::string spritePath;

	int anchoTot;
	int altoTot;
	SDL_Rect currentClip;


};

#endif
