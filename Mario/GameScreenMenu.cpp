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

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	mGunShot = new SoundEffect(1, "Music/9mm.wav", 0);

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
	CharacterKoopa* koopaCharacter;
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D(position), direction, speed);
	mEnemies.push_back(koopaCharacter);
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

	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	if (gCharacterMario->GetState() == 1)
	{
		gCharacterMario->Update(deltaTime, e);
	}

	if (gCharacterLuigi->GetState() == 1)
	{
		gCharacterLuigi->Update(deltaTime, e);
	}

	gCharacterLuigi->CheckViewportCollision();
	gCharacterMario->CheckViewportCollision();
	UpdatePOWBlock();

	koopaRespawnTimer -= deltaTime;

	if (koopaRespawnTimer <= 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		koopaRespawnTimer = KOOPA_RESPAWN_TIME;
	}

	UpdateEnemies(deltaTime, e);
}

void GameScreenMenu::UpdatePOWBlock()
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

			//collision checks with player and enemy
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//behind pipe ignore collisions
			}
			else
			{

				if (mEnemies[i]->KoopaState())
				{
					if (Collisions::Instance()->Circle(mEnemies[i], gCharacterMario))
					{
						//slide of screen
						mEnemies[i]->SetAlive(false);
					}
					if (Collisions::Instance()->Circle(mEnemies[i], gCharacterLuigi))
					{
						//slide of screen
						mEnemies[i]->SetAlive(false);
					}
				}

				if (!mEnemies[i]->KoopaState())
				{
					if (Collisions::Instance()->Circle(mEnemies[i], gCharacterMario))
					{
						gCharacterMario->SetState(CHARACTERSTATE_DEAD);
					}
					if (Collisions::Instance()->Circle(mEnemies[i], gCharacterLuigi))
					{
						gCharacterLuigi->SetState(CHARACTERSTATE_DEAD);
					}
				}

			}

			//schedule dead enemy for deletion
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove a dead enemy
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenMenu::Render()
{
	//Draw Enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	if (gCharacterMario->GetState() == 1)
	{
		gCharacterMario->Render();
	}

	if(gCharacterLuigi->GetState() == 1)
	{
		gCharacterLuigi->Render();
	}

	mPowBlock->Render();
}

void GameScreenMenu::ScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
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