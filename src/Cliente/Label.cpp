#include "Label.h"


Label::Label(){};


void Label::setData(SDL_Renderer* gRend, string text, int size){
	gTextTexture.gRenderer = gRend;
	ltext = text;
	lsize = size;
}

bool Label::loadMedia()
{
	bool success = true;

	//Initialize SDL_ttf
	if( TTF_Init() == -1 ){
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}else{
		//Open the font
		gFont = TTF_OpenFont( "munro_small.ttf", lsize );
		if( gFont == NULL )
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
			success = false;
		}
		else
		{
			gTextTexture.gFont = gFont;
			//Render text
			SDL_Color textColor = { 0, 0, 0 };

			if( !gTextTexture.loadFromRenderedText( ltext, textColor ) )
			{
				printf( "Failed to render text texture!\n" );
				success = false;
			}
		}
	}
	return success;
}


void Label::close()
{
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
}


Label::~Label()
{
	close();
}


void Label::setDefaultPos(int x, int y){
	this->defaultX = x;
	this->defaultY = y;
}
void Label::render(int posX, int posY){
	gTextTexture.render( posX,  posY);
}

void Label::renderDefault(){

	SDL_Color textColor = { 255, 255, 255 };
	gTextTexture.loadFromRenderedText( ltext, textColor );
	gTextTexture.render( defaultX,  defaultY);

}
