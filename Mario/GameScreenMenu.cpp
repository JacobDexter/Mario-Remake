#include "GameScreenMenu.h"

using namespace std;

extern GameScreenManager* gameScreenManager;

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

bool GameScreenMenu::SetUpLevel()
{
	//Load Background
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/MenuBackground.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	//Load Text
	menuText = new Text();
	menuFont = TTF_OpenFont("Fonts/emulogic.ttf", 18);

	if (menuFont == NULL)
	{
		cout << "Error opening font: " << SDL_GetError() << endl;
		return false;
	}

	menuText->Setup(mRenderer, 256, 270, "Click to start the game!", menuFont, { 255, 255, 255, 0 }, &menuTexture, &menuRect, menuSurface);
	menuRect.x -= menuRect.w * 0.5f;

	return true;
}

void GameScreenMenu::Render()
{
	//Background Render
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	//Text Render
	menuText->Render(mRenderer, menuTexture, &menuRect);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		//change screens
		gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
	break;
	}
}

GameScreenMenu::~GameScreenMenu()
{
	//clear background
	mBackgroundTexture = NULL;
	delete mBackgroundTexture;

	//clear text
	menuText = NULL;
	delete menuText;
}