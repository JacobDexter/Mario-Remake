#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	gCharacter->Update(deltaTime, e);
}

void GameScreenLevel1::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	gCharacter->Render();
}


GameScreenLevel1::~GameScreenLevel1()
{
	//clear background
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	//clear character
	delete gCharacter;
	gCharacter = NULL;
}