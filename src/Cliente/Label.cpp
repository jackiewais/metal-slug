#include "Label.h"


Label::Label(){};


void Label::setData(SDL_Renderer* gRend, string text, int size){
	gTextTexture.gRenderer = gRend;
	ltext = text;
	lsize = size;

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}else if( !loadMedia())
	{
		printf( "Failed to load media!\n" );
	}

}

bool Label::loadMedia()
{
	//Loading success flag
	bool success = true;

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

void Label::render(int posX, int posY){
	gTextTexture.render( posX,  posY);
}
