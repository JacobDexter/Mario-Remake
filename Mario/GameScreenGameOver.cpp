#include "GameScreenGameOver.h"

using namespace std;

extern GameScreenManager* gameScreenManager;
extern int score;

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

bool GameScreenGameOver::SetUpLevel()
{
	//Load Background
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/GameOverBackground.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	//Open font
	marioFont = TTF_OpenFont("Fonts/emulogic.ttf", 20);

	if (marioFont == NULL)
	{
		cout << "Error opening font: " << SDL_GetError() << endl;
	}

	//Navigation font
	navigationFont = TTF_OpenFont("Fonts/emulogic.ttf", 8);

	if (navigationFont == NULL)
	{
		cout << "Error opening font: " << SDL_GetError() << endl;
	}

	//Game over font
	gameOverFont = TTF_OpenFont("Fonts/emulogic.ttf", 40);

	if (gameOverFont == NULL)
	{
		cout << "Error opening font: " << SDL_GetError() << endl;
	}

	//Convert int to string
	string scoreString;
	ostringstream convert;

	convert << score;
	scoreString = convert.str();

	//Scoreboard Text
	scoreboard = new Text();
	scoreboard->Setup(mRenderer, 70, 0, "SCORE:", marioFont, { 255, 0, 0, 0 }, &scoreTexture, &scoreRect, scoreSurface);
	
	//Score Number Text
	scoreNum = new Text();
	scoreNum->Setup(mRenderer, (scoreRect.x + scoreRect.w + 3), 0, scoreString.c_str(), marioFont, { 255, 255, 255, 0 }, &scoreNumTexture, &scoreNumRect, scoreNumSurface);

	//Navigation Text
	navigation = new Text();
	navigation->Setup(mRenderer, 0, 360, "CLICK - Continue to the leaderboard!", navigationFont, { 255, 255, 255, 0 }, &navigationTexture, &navigationRect, navigationSurface);
	navigationRect.x = (SCREEN_WIDTH / 2) - (navigationRect.w / 2); //CENTER TEXT

	//GameOver Text
	gameOver = new Text();
	gameOver->Setup(mRenderer, 0, 120, "GAME OVER", gameOverFont, { 255, 0, 0, 0 }, &gameOverTexture, &gameOverRect, gameOverSurface);
	gameOverRect.x = (SCREEN_WIDTH / 2) - (gameOverRect.w / 2); //CENTER TEXT
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		//change screens
		gameScreenManager->ChangeScreen(SCREEN_LEADERBOARD);
		break;
	}
}

void GameScreenGameOver::Render()
{
	//Background Render
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	//text render
	scoreboard->Render(mRenderer, scoreTexture, &scoreRect);
	scoreNum->Render(mRenderer, scoreNumTexture, &scoreNumRect);

	//navigation text
	navigation->Render(mRenderer, navigationTexture, &navigationRect);

	//game over text
	gameOver->Render(mRenderer, gameOverTexture, &gameOverRect);
}

GameScreenGameOver::~GameScreenGameOver()
{
	//clear background
	mBackgroundTexture = NULL;
	delete mBackgroundTexture;

	//clear text
	scoreboard = NULL;
	scoreNum = NULL;
	gameOver = NULL;
	navigation = NULL;
	delete scoreboard;
	delete scoreNum;
	delete gameOver;
	delete navigation;

	//destroy text textures
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(scoreNumTexture);
	SDL_DestroyTexture(gameOverTexture);
	SDL_DestroyTexture(navigationTexture);
}