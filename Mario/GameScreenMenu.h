#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"

class Texture2D;
class Character;

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	//variables
	Texture2D* mBackgroundTexture;
	Character* gCharacter;
	LevelMap* mLevelMap;

	//functions
	bool SetUpLevel();
	void SetLevelMap();
};