#include "GameScreenLeaderboard.h"

extern GameScreenManager* gameScreenManager;
extern int score;

GameScreenLeaderboard::GameScreenLeaderboard(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

bool GameScreenLeaderboard::SetUpLevel()
{
	//Load Background
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/LeaderboardBackground.png"))
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
	
	//Leaderboard textOpen font
	leaderboardFont = TTF_OpenFont("Fonts/emulogic.ttf", 28);

	if (leaderboardFont == NULL)
	{
		cout << "Error opening font: " << SDL_GetError() << endl;
	}

	//Navigation open font
	navigationFont = TTF_OpenFont("Fonts/emulogic.ttf", 8);

	if (navigationFont == NULL)
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
	navigation->Setup(mRenderer, 0, 360, "ESC - Back to menu! CLICK - Play Again!", navigationFont, { 255, 255, 255, 0 }, &navigationTexture, &navigationRect, navigationSurface);
	navigationRect.x = (SCREEN_WIDTH / 2) - (navigationRect.w / 2);

	LoadLeadboardFromFile("Leaderboard.txt");
	SetupLeaderboardText();
}

bool GameScreenLeaderboard::LoadLeadboardFromFile(string path)
{
	ifstream inFile;

	inFile.open(path);

	if (!inFile.good())
	{
		cerr << "Can't open scoreboard file." << endl;
		return false;
	}

	//Save all
	for (int x = 0; x < 10; x++)
	{
		string temp;
		inFile >> temp;
		scores.push_back(temp);
	}

	inFile.close();

	return true;
}

bool GameScreenLeaderboard::SetupLeaderboardText()
{
	//Leaderboard Text
	leaderboardText = new Text();
	scoreNum->Setup(mRenderer, 0, 60, "LEADERBOARD", leaderboardFont, { 255, 255, 255, 0 }, &leaderboardTextTexture, &leaderboardTextRect, leaderboardTextSurface);
	leaderboardTextRect.x = (SCREEN_WIDTH / 2) - (leaderboardTextRect.w / 2);

	//Leaderboard Scores
	int yPosition = 90.0f;
	for (int x = 0; x < scores.size(); x++)
	{
		leaderboard[x] = new Text();
		yPosition += 20;
		leaderboard[x]->Setup(mRenderer, 0, yPosition, scores[x].c_str(), marioFont, { 255, 0, 0, 0 }, &leaderboardTexture[x], &leaderboardRect[x], leaderboardSurface[x]);
		leaderboardRect[x].x = (SCREEN_WIDTH / 2) - (leaderboardRect[x].w / 2);
	}

	return true;
}

void GameScreenLeaderboard::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		//change screens
		gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			gameScreenManager->ChangeScreen(SCREEN_MENU);
			break;
		}
	}
}

void GameScreenLeaderboard::Render()
{
	//Background Render
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	//text render
	scoreboard->Render(mRenderer, scoreTexture, &scoreRect);
	scoreNum->Render(mRenderer, scoreNumTexture, &scoreNumRect);

	//leaderboard text
	leaderboardText->Render(mRenderer, leaderboardTextTexture, &leaderboardTextRect);

	//navigation text
	navigation->Render(mRenderer, navigationTexture, &navigationRect);

	for (int x = 0; x < scores.size(); x++)
	{
		leaderboard[x]->Render(mRenderer, leaderboardTexture[x], &leaderboardRect[x]);
	}
}

GameScreenLeaderboard::~GameScreenLeaderboard()
{
	//clear background
	mBackgroundTexture = NULL;
	delete mBackgroundTexture;

	//clear text
	scoreboard = NULL;
	scoreNum = NULL;
	leaderboardText = NULL;
	navigation = NULL;
	delete scoreboard;
	delete scoreNum;
	delete leaderboardText;
	delete navigation;

	for (int x = 0; x < 10; x++)
	{
		leaderboard[x] = NULL;
		delete leaderboard[x];
	}

	//destroy text textures
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(scoreNumTexture);
	SDL_DestroyTexture(leaderboardTextTexture);
	SDL_DestroyTexture(navigationTexture);

	for (int x = 0; x < scores.size(); x++)
	{
		SDL_DestroyTexture(leaderboardTexture[x]);
	}
}