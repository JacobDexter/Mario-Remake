#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	SetUpLevel();
}

bool GameScreenMenu::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	SetLevelMap();

	gCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
}

void GameScreenMenu::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	mLevelMap = new LevelMap(map);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	gCharacter->Update(deltaTime, e);
}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	gCharacter->Render();
}

GameScreenMenu::~GameScreenMenu()
{
	//clear background
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	//clear character
	delete gCharacter;
	gCharacter = NULL;
}