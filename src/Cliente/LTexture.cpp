#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Escenario.h"

LTexture::LTexture(Escenario *escenario, std::string path)
{
	//Initialize
	this->mTexture = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
	this->widthScaled = 0;
	this->heightScaled = 0;
	this->escenario = escenario;
	this->path = path;

}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile()
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( this->path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", this->path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( this->escenario->getGRenderer(), loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", this->path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
	}
}

void LTexture::render( int x, int y )
{
	int anchoFrame = mWidth;
	int altoFrame = mHeight;
	int anchoRender = this->getWidth();
	int altoRender = this->getHeight();

	// Esto por ahora esta harcodeado
	if (this->path == "images/jugador.png") {
		anchoFrame = 37;
		altoFrame = 49;
		anchoRender = 37;
		altoRender = 49;
	}

	SDL_Rect frame = { 0, 0, anchoFrame, altoFrame };
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, anchoRender, altoRender };
	SDL_RenderCopy( this->escenario->getGRenderer(), mTexture, &frame, &renderQuad );
}

int LTexture::getWidth()
{
	if (this->widthScaled == 0) {
		return this->mWidth;
	}
	return this->widthScaled;
}

int LTexture::getHeight()
{
	if (this->heightScaled == 0) {
		return this->mHeight;
	}
	return this->heightScaled;
}

void LTexture::setWidth(int mWidth)
{
	this->widthScaled = mWidth;
}

void LTexture::setHeight(int mHeight)
{
	this->heightScaled = mHeight;
}

void LTexture::setPath(std::string path)
{
	this->path = path;
}
