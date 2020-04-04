#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : CharacterEnemy(renderer, imagePath, startPosition, map)
{
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mFacingDirection = startFacing;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();

	//animation
	spriteInterval = 0.3f;
	spritePortion = 0;
	spriteChangeTimer = spriteInterval;

	//sound
	sCoinCollect = new SoundEffect(0, "Sounds/Coin.wav", 0);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	spriteChangeTimer -= deltaTime;

	//Timer to change the sprite being used
	if (spriteChangeTimer <= 0.0f)
	{
		if (spritePortion < 3)
		{
			spritePortion++;
			spriteChangeTimer = spriteInterval;
		}
		else if (spritePortion == 3)
		{
			spritePortion = 0;
			spriteChangeTimer = spriteInterval;
		}
	}

	//Deciedes the origin(far left side) of the sprite (4 States)
	if (spritePortion == 0)//full coin
	{
		spriteOrigin = 0.0f;
	}
	else if (spritePortion == 1)//turned coin
	{
		spriteOrigin = mSingleSpriteWidth;
	}
	else if (spritePortion == 2)//side coin
	{
		spriteOrigin = (mSingleSpriteWidth * 2);
	}
	else if (spritePortion == 3)//turned coin
	{
		spriteOrigin = mSingleSpriteWidth;
	}

	//Checks what way coin is facing and moves it that direction
	if (mFacingDirection == FACING_LEFT)
	{
		mMovingLeft = true;
		mMovingRight = false;
	}
	else if (mFacingDirection == FACING_RIGHT)
	{
		mMovingLeft = false;
		mMovingRight = true;
	}
}

void CharacterCoin::Render()
{
	SDL_Rect portionOfSpritesheet = { spriteOrigin, 0, mSingleSpriteWidth, mSingleSpriteHeight }; //select portion of spritesheet
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight }; //draw position

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= mMovementSpeed * deltaTime;
}

void CharacterCoin::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += mMovementSpeed * deltaTime;
}

void CharacterCoin::CollectCoin()
{
	Jump();
	sCoinCollect->Play();
	mCoinCollected = true;
}

bool CharacterCoin::GetCollected()
{
	return mCoinCollected;
}

void CharacterCoin::SetCollected(bool state)
{
	mCoinCollected = state;
}