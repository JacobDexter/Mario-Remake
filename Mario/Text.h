#pragma once

#ifndef _TEXT_H
#define _TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Constants.h"

class Text
{
public:
	//constructor/destructor
	Text();
	~Text();

	//Update Functions
	void Render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect);

	//custom functions
	void Setup(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font* font, SDL_Color textColor, SDL_Texture** texture, SDL_Rect* rect);
	float GetWidth();
	float GetHeight();

private:
	float text_width;
	float text_height;
	char* textContents;
};

#endif