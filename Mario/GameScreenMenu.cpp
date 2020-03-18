#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"
#include "Collisions.h"

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

	gCharacterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	gCharacterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(64, 330), mLevelMap);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	mScreenShake = false;
	mBackgroundYPos = 0.0f;
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

void GameScreenMenu::CreateKoopa(Vector2D position, FACING direction, float speed)
{

}

void GameScreenMenu::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(gCharacterMario->GetCollisionBox(), mPowBlock->GetCollisionBox()) || Collisions::Instance()->Box(gCharacterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (gCharacterMario->isJumping())
			{
				ScreenShake();
				mPowBlock->TakeAHit();
				gCharacterMario->CancelJump();
			}
			else if (gCharacterLuigi->isJumping())
			{
				ScreenShake();
				mPowBlock->TakeAHit();
				gCharacterLuigi->CancelJump();
			}
		}
	}
}

void GameScreenMenu::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			if (mEnemies[i]->GetPosition().y > 300.0f) //Check to see if enemy is on bottom tile row
			{
				//checks if enemy is off screen left/right
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);
				}
			}

			mEnemies[i]->Update(deltaTime, e); //update enemy
		}
	}
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
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

	gCharacterMario->Update(deltaTime, e);
	gCharacterLuigi->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
}

void GameScreenMenu::Render()
{
	//Draw Enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	gCharacterMario->Render();
	gCharacterLuigi->Render();
	mPowBlock->Render();
}

void GameScreenMenu::ScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

GameScreenMenu::~GameScreenMenu()
{
	//clear background
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	//clear character
	delete gCharacterMario;
	delete gCharacterLuigi;
	gCharacterMario = NULL;
	gCharacterLuigi = NULL;

	//clear pow block
	delete mPowBlock;
	mPowBlock = NULL;

	//clear enemies
	mEnemies.clear();
}