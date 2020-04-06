#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : CharacterEnemy(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	mKoopaIsAlive = true;
	ShellHit = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if(!mInjured)
	{ 
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
	else
	{
		mMovingRight = false;
		mMovingLeft = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightWayUp();
	}

	if (ShellHit)
	{
		mPosition.y += deltaTime * 400;
		mPosition.x += deltaTime * 350;
		mInjuredTime = 5.0f;
	}
}

void CharacterKoopa::Render()
{
	int left = 0.0f; //stores left position of sprite

	if (mInjured)
		left = mSingleSpriteWidth; //left position to be the left position of the second image on spritesheet

	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight }; //select portion of spritesheet

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight }; //draw position

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void CharacterKoopa::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= mMovementSpeed * deltaTime;
}

void CharacterKoopa::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += mMovementSpeed * deltaTime;
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::FlipRightWayUp()
{
	mFacingDirection != mFacingDirection;
	mInjured = false;
	Jump();
}

bool CharacterKoopa::GetAlive()
{
	return mKoopaIsAlive;
}

void CharacterKoopa::SetAlive(bool state)
{
	mKoopaIsAlive = state;
}

bool CharacterKoopa::KoopaState()
{
	return mInjured;
}