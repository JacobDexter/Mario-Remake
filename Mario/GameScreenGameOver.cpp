#include "GameScreenGameOver.h"

using namespace std;

extern GameScreenManager* gameScreenManager;

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

bool GameScreenGameOver::SetUpLevel()
{
	//Load Background
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/Level1.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{

}

void GameScreenGameOver::Render()
{
	//Background Render
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

GameScreenGameOver::~GameScreenGameOver()
{
	//clear background
	mBackgroundTexture = NULL;
	delete mBackgroundTexture;
}