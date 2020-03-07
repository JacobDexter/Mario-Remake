#pragma once

#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include "SDL.h"
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
};

#endif // _GAMESCREENMANAGER_H