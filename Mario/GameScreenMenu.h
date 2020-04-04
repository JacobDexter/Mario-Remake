#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Text.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "Mario.h"

class Texture2D;
class GameScreen;
class GameScreenManager;

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();

private:
	//variables
	Texture2D* mBackgroundTexture;

	//Text
	Text* menuText;
	TTF_Font* menuFont;
	SDL_Texture* menuTexture;
	SDL_Rect menuRect;
};