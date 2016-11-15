#include "LTextureBasic.h"

#include <iostream>

using namespace std;


class Label {
	public:
		Label();
		void setData(SDL_Renderer* gRend, string text, int size);
		bool loadMedia();
		void close();
		void render(int posX, int posY);
		void renderDefault();
		int defaultX = 0;
		int defaultY = 0;
		void setDefaultPos(int x, int y);
	private:
		string ltext;
		int lsize;
		LTextureBasic gTextTexture;
		TTF_Font *gFont = NULL;


};
