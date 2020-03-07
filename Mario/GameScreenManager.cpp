#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;

	ChangeScreen(startScreen);
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenMenu* tempScreen;
	GameScreenLevel1* tempScreen1;

	switch (newScreen)
	{
		case SCREEN_MENU:
			tempScreen = new GameScreenMenu(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen;
			tempScreen = NULL;
			return;
		case SCREEN_LEVEL1:
			tempScreen1 = new GameScreenLevel1(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
			return;
		break;
	}
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}