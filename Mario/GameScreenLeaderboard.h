#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Text.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "Mario.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Texture2D;
class GameScreen;
class GameScreenManager;

using namespace std;

class GameScreenLeaderboard : GameScreen
{
public:
	GameScreenLeaderboard(SDL_Renderer* renderer);
	~GameScreenLeaderboard();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	//Level Setup
	bool SetUpLevel();

	//Leaderboard
	bool LoadLeadboardFromFile(string path);
	bool SetupLeaderboardText();

private:
	//variables
	Texture2D* mBackgroundTexture;
	vector<string> scores;

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

	//LEADERBOARD
	Text* leaderboard[10];
	SDL_Texture* leaderboardTexture[10];
	SDL_Rect leaderboardRect[10];
	SDL_Surface* leaderboardSurface[10];

	//LEADERBOARD TEXT
	Text* leaderboardText;
	TTF_Font* leaderboardFont;
	SDL_Texture* leaderboardTextTexture;
	SDL_Rect leaderboardTextRect;
	SDL_Surface* leaderboardTextSurface;

	//NAVIGATION TEXT
	Text* navigation;
	TTF_Font* navigationFont;
	SDL_Texture* navigationTexture;
	SDL_Rect navigationRect;
	SDL_Surface* navigationSurface;
};

