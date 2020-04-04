#include "Text.h"

using namespace std;

Text::Text()
{
	text_width = NULL;
	text_height = NULL;
}

void Text::Render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect)
{
	//Text Render
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

Text::~Text()
{

}

void Text::Setup(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font* font, SDL_Color textColor, SDL_Texture** texture, SDL_Rect *rect)
{
	SDL_Surface* surface;

	//Create surface
	if (!(surface = TTF_RenderText_Solid(font, text, textColor)))
	{
		cout << "Failed to create surface: " << SDL_GetError() << endl;
		return;
	}

	//create texture with surface
	*texture = SDL_CreateTextureFromSurface(renderer, surface);

	//save surface size data to variables
	text_width = surface->w;
	text_height = surface->h;

	rect->x = x;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;

	//free surface memory
	SDL_FreeSurface(surface);
}

float Text::GetWidth()
{
	return text_width;
}

float Text::GetHeight()
{
	return text_height;
}