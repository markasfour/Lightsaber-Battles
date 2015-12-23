#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

//Texture wrapper class
class LTexture
{
	public:

	//the actual hardware texture
	SDL_Texture *mTexture;

	//image dimensions
	int mWidth;
	int mHeight;
	
	//init variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//loads image from path
	bool loadFromFile(string path, SDL_Renderer *RENDERER);

	//renders texture at given point
	void render(int x, int y);

	//deallocates texture
	void free();
};

LTexture::LTexture()
{
	//init
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//deallocate
	free();
}

bool LTexture::loadFromFile(string path, SDL_Renderer *RENDERER)
{
	//remove preexisting texture
	free();

	//the final texture
	SDL_Texture *newTexture = NULL;

	//load image from path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image. SDL_image Error: " << IMG_GetError();
	}
	else
	{
		//create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(RENDERER, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to crate texture. SDL_Error: " << SDL_GetError();
		}
		else
		{
			//get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//remove old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

#endif
