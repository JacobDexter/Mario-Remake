#include "GameScreenLevel1.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Texture2D.h"
#include "PowBlock.h"
#include "Collisions.h"

using namespace std;

extern GameScreenManager* gameScreenManager;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	gameOver = false;
	score = 0;
	SetUpLevel();
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Level1.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	SetLevelMap();

	//Open Font
	marioFont = TTF_OpenFont("Fonts/emulogic.ttf", 20);

	if (marioFont == NULL)
	{
		cout << "Error opening font: " << SDL_GetError() << endl;
	}

	//Scoreboard Text
	scoreboard = new Text();
	scoreboard->Setup(mRenderer, 70, 0, "SCORE:", marioFont, { 255, 0, 0, 0 }, &scoreTexture, &scoreRect, scoreSurface);

	//Score Number Text
	scoreNum = new Text();
	scoreNum->Setup(mRenderer, (scoreRect.x + scoreRect.w + 3), 0, "0", marioFont, { 255, 255, 255, 0 }, &scoreNumTexture, &scoreNumRect, scoreNumSurface);

	//Players setup
	gCharacterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	gCharacterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(64, 330), mLevelMap);

	//Pow Block setup
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	//music setup
	gBackgroundMusic = new Music();
	gBackgroundMusic->LoadMusic("Music/Mario.ogg");

	//Sounds setup
	sKoopaSpawn = new SoundEffect(1, "Sounds/KoopaSpawn.wav", 0);
	sGameOver = new SoundEffect(1, "Sounds/GameOver.wav", 0);
	sPlayerDeath = new SoundEffect(2, "Sounds/Death.wav", 0);
	sKoopaKick = new SoundEffect(2, "Sounds/KoopaKick.wav", 0);

	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//Spawn initial enemies
	CreateKoopa(Vector2D(10, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(470, 32), FACING_LEFT, KOOPA_SPEED);
	CreateCoin(Vector2D(370, 32), FACING_LEFT, KOOPA_SPEED);
	CreateCoin(Vector2D(170, 32), FACING_RIGHT, KOOPA_SPEED);

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH];
	ifstream inFile;

	inFile.open("Maps/Level1.txt");

	if (!inFile.good())
	{
		cerr << "Can't open map file." << endl;
		return;
	}

	//Load map from file into 3D array
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			inFile >> map[h][w];
		}
	}

	inFile.close();

	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//create level map with map data loaded from file
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter;
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D(position), direction, speed);
	sKoopaSpawn->Play();
	mKoopas.push_back(koopaCharacter); //adds koopa to vector container
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction, float speed)
{
	CharacterCoin* coinCharacter;
	coinCharacter = new CharacterCoin(mRenderer, "Images/Coin.png", mLevelMap, Vector2D(position), direction, speed);
	mCoins.push_back(coinCharacter); //adds coin to vector container
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Screenshake if pow block is damaged
	if (mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenShakeTime <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	if (gCharacterMario->GetState() == 1)
	{
		gCharacterMario->Update(deltaTime, e);
	}
	else if(gCharacterMario->GetPosition().y < SCREEN_HEIGHT)
	{
		gCharacterMario->PlayerDeath(deltaTime);
	}

	if (gCharacterLuigi->GetState() == 1)
	{
		gCharacterLuigi->Update(deltaTime, e);
	}
	else if (gCharacterLuigi->GetPosition().y < SCREEN_HEIGHT)
	{
		gCharacterLuigi->PlayerDeath(deltaTime);
	}

	if (gCharacterLuigi->GetState() == 1 || gCharacterMario->GetState() == 1)
	{

		gCharacterLuigi->CheckViewportCollision();
		gCharacterMario->CheckViewportCollision();

		koopaRespawnTimer -= deltaTime;

		//Timer to respawn Koopas
		if (koopaRespawnTimer <= 0.0f)
		{
			CreateKoopa(Vector2D(10, 32), FACING_RIGHT, KOOPA_SPEED);
			CreateKoopa(Vector2D(470, 32), FACING_LEFT, KOOPA_SPEED);
			koopaRespawnTimer = KOOPA_RESPAWN_TIME;
		}

		//Update Enemies and Blocks
		UpdatePOWBlock();
		UpdateEnemies(deltaTime, e);
	}
	else if (gameOver) //Game Over condition
	{
		if (Mix_Playing(1) != 1)
		{
			//Display Game Over
			gameScreenManager->ChangeScreen(SCREEN_GAMEOVER);
		}
	}
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(gCharacterMario->GetCollisionBox(), mPowBlock->GetCollisionBox()) || Collisions::Instance()->Box(gCharacterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (gCharacterMario->isJumping() && gCharacterMario->GetState() == 1)
			{
				ScreenShake();
				mPowBlock->TakeAHit();
				gCharacterMario->CancelJump();
			}
			else if (gCharacterLuigi->isJumping() && gCharacterLuigi->GetState() == 1)
			{
				ScreenShake();
				mPowBlock->TakeAHit();
				gCharacterLuigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//Update Koopas
	if (!mKoopas.empty())
	{
		int enemyIndexToDelete = -1;

		for (unsigned int i = 0; i < mKoopas.size(); i++)
		{
			if (mKoopas[i]->GetPosition().y > 300.0f) //Check to see if enemy is on bottom tile row
			{
				//checks if enemy is off screen left/right
				if (mKoopas[i]->GetPosition().x < (float)(-mKoopas[i]->GetCollisionBox().width * 0.5f) || mKoopas[i]->GetPosition().x > SCREEN_WIDTH - (float)(mKoopas[i]->GetCollisionBox().width * 0.55f))
				{
					mKoopas[i]->SetAlive(false);
				}
			}

			mKoopas[i]->Update(deltaTime, e); //update enemy

			//collision checks with player and enemy
			if ((mKoopas[i]->GetPosition().y > 300.0f || mKoopas[i]->GetPosition().y <= 64.0f) && (mKoopas[i]->GetPosition().x < 64.0f || mKoopas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//behind pipe ignore collisions
			}
			else
			{

				if (mKoopas[i]->KoopaState())
				{
					if (Collisions::Instance()->Circle(mKoopas[i], gCharacterMario))
					{
						//hit of screen
						if (!mKoopas[i]->ShellHit)
						{
							sKoopaKick->Play();
							score += 800;
							UpdateScoreText(score);
						}

						mKoopas[i]->ShellHit = true;
					}
					if (Collisions::Instance()->Circle(mKoopas[i], gCharacterLuigi))
					{
						//hit of screen
						if (!mKoopas[i]->ShellHit)
						{
							sKoopaKick->Play();
							score += 800;
							UpdateScoreText(score);
						}

						mKoopas[i]->ShellHit = true;
					}
				}

				if (!mKoopas[i]->KoopaState())
				{
					if (Collisions::Instance()->Circle(mKoopas[i], gCharacterMario))
					{
						sPlayerDeath->Play();
						gCharacterMario->SetState(CHARACTERSTATE_DEAD);

						if (gCharacterLuigi->GetState() == CHARACTERSTATE_DEAD)
						{
							gBackgroundMusic->Stop();
							sGameOver->Play();
							gameOver = true;
						}
					}
					if (Collisions::Instance()->Circle(mKoopas[i], gCharacterLuigi))
					{
						sPlayerDeath->Play();
						gCharacterLuigi->SetState(CHARACTERSTATE_DEAD);

						if (gCharacterMario->GetState() == CHARACTERSTATE_DEAD)
						{
							gBackgroundMusic->Stop();
							sGameOver->Play();
							gameOver = true;
						}
					}
				}

			}

			//schedule dead enemy for deletion
			if (!mKoopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove a dead enemy
		if (enemyIndexToDelete != -1)
		{
			mKoopas.erase(mKoopas.begin() + enemyIndexToDelete);
		}
	}

	//Coins
	if (!mCoins.empty())
	{
		int enemyIndexToDelete = -1;

		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			//checks if enemy is off screen left/right
			if (mCoins[i]->GetPosition().x < (float)(-mCoins[i]->GetCollisionBox().width * 0.5f) || mCoins[i]->GetPosition().x > SCREEN_WIDTH + (float)(mCoins[i]->GetCollisionBox().width * 0.55f))
			{
				mCoins[i]->SetCollected(true);
			}

			mCoins[i]->Update(deltaTime, e); //update enemy

			if (!mCoins[i]->GetCollected())
			{
				if (Collisions::Instance()->Circle(mCoins[i], gCharacterMario))
				{
					mCoins[i]->CollectCoin();
					UpdateScoreText(score);
					score += 800;
				}
				if (Collisions::Instance()->Circle(mCoins[i], gCharacterLuigi))
				{
					mCoins[i]->CollectCoin();
					score += 800;
					UpdateScoreText(score);
				}
			}

			//schedule dead enemy for deletion
			if (mCoins[i]->GetCollected())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove a dead enemy
		if (enemyIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::Render()
{
	//Draw Enemies
	for (unsigned int i = 0; i < mKoopas.size(); i++)
	{
		mKoopas[i]->Render();
	}
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

	//background render
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	//text render
	scoreboard->Render(mRenderer, scoreTexture, &scoreRect);
	scoreNum->Render(mRenderer, scoreNumTexture, &scoreNumRect);

	if (gCharacterMario->GetState() == 1 || gCharacterMario->GetPosition().y < SCREEN_HEIGHT)
	{
		gCharacterMario->Render();
	}

	if(gCharacterLuigi->GetState() == 1 || gCharacterLuigi->GetPosition().y < SCREEN_HEIGHT)
	{
		gCharacterLuigi->Render();
	}

	mPowBlock->Render();
}

void GameScreenLevel1::ScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	//Effect Enemies
	for (unsigned int i = 0; i < mKoopas.size(); i++)
	{
		mKoopas[i]->TakeDamage();
		score += 10;
		UpdateScoreText(score);
	}
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->CollectCoin();
		score += 800;
		UpdateScoreText(score);
	}
}

void GameScreenLevel1::UpdateScoreText(int score)
{
	string scoreString;
	ostringstream convert;

	convert << score;
	scoreString = convert.str();

	scoreNum->Setup(mRenderer, (scoreRect.x + scoreRect.w + 3), 0, scoreString.c_str(), marioFont, { 255, 255, 255, 0 }, &scoreNumTexture, &scoreNumRect, scoreNumSurface);
}

GameScreenLevel1::~GameScreenLevel1()
{
	//clear background
	mBackgroundTexture = NULL;
	delete mBackgroundTexture;

	//clear level map
	mLevelMap = NULL;
	delete mLevelMap;

	//clear character
	gCharacterMario = NULL;
	gCharacterLuigi = NULL;
	delete gCharacterMario;
	delete gCharacterLuigi;

	//clear pow block
	mPowBlock = NULL;
	delete mPowBlock;

	//clear text
	scoreboard = NULL;
	scoreNum = NULL;
	delete scoreboard;
	delete scoreNum;

	//clear enemies
	mKoopas.clear();
	mCoins.clear();

	//clear sound effects
	sKoopaSpawn = NULL;
	delete sKoopaSpawn;
	sGameOver = NULL;
	delete sGameOver;
	gBackgroundMusic = NULL;
	delete gBackgroundMusic;
	sPlayerDeath = NULL;
	delete sPlayerDeath;

	//destroy text textures
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(scoreNumTexture);
}