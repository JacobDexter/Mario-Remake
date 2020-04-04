#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Text.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "Mario.h"
#include <fstream>

class Texture2D;
class GameScreen;
class GameScreenManager;

class GameScreenLeaderboard : GameScreen
{
public:
	GameScreenLeaderboard(SDL_Renderer* renderer);
	~GameScreenLeaderboard();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();
	bool LoadLeadboardFromFile(string path);

private:
	//variables
	Texture2D* mBackgroundTexture;
	int scores[10];
};

