#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	//variables
	Texture2D* mBackgroundTexture;
	Character* gCharacter;

	//functions
	bool SetUpLevel();
};