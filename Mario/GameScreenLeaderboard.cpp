#include "GameScreenLeaderboard.h"

using namespace std;

extern GameScreenManager* gameScreenManager;

GameScreenLeaderboard::GameScreenLeaderboard(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

bool GameScreenLeaderboard::SetUpLevel()
{
	//Load Background
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/Level1.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	LoadLeadboardFromFile("Leaderboard.txt");
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

	for (int x = 0; x < 10; x++)
	{
		inFile >> scores[x];
	}

	inFile.close();

	return true;
}

void GameScreenLeaderboard::Update(float deltaTime, SDL_Event e)
{

}

void GameScreenLeaderboard::Render()
{
	//Background Render
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

GameScreenLeaderboard::~GameScreenLeaderboard()
{
	//clear background
	mBackgroundTexture = NULL;
	delete mBackgroundTexture;
}