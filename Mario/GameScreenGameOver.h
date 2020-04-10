#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Text.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "GameScreenLevel1.h"
#include "Mario.h"
#include "Music.h"
#include <string>
#include <sstream>

class Texture2D;
class GameScreen;
class GameScreenManager;

class GameScreenGameOver : GameScreen
{
public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();

private:
	//variables
	Texture2D* mBackgroundTexture;

	//Text
	//SCORE TEXT
	Text* scoreboard;
	TTF_Font* marioFont;
	SDL_Texture* scoreTexture;
	SDL_Rect scoreRect;
	SDL_Surface* scoreSurface;

	//SCORE NUMBER
	Text* scoreNum;
	SDL_Texture* scoreNumTexture;
	SDL_Rect scoreNumRect;
	SDL_Surface* scoreNumSurface;

	//NAVIGATION TEXT
	Text* navigation;
	TTF_Font* navigationFont;
	SDL_Texture* navigationTexture;
	SDL_Rect navigationRect;
	SDL_Surface* navigationSurface;

	//GAME OVER TEXT
	Text* gameOver;
	TTF_Font* gameOverFont;
	SDL_Texture* gameOverTexture;
	SDL_Rect gameOverRect;
	SDL_Surface* gameOverSurface;
};

