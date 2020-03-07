#include "Texture2D.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mWidth = NULL;
	mHeight = NULL;
	mTexture = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	Free();

	//Load image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		mWidth = pSurface->w;
		mHeight = pSurface->h;
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}

		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
	}

	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		
		mWidth, mHeight = 0;
		mTexture = NULL;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
}

Texture2D::~Texture2D()
{
	Free();

	mRenderer = NULL;
}