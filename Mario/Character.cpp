#include "Character.h"
#include "CharacterMario.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	//Character Setup Definitions
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	
	//Character Movement Definitions
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCanJump = true;

	//Character Collisions
	mCollisionRadius = 15.0f;

	//level map setup
	mCurrentLevelMap = map;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(GetPosition(), SDL_FLIP_NONE);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(GetPosition(), SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		mCanJump = true;
	}

	if (mJumping)
	{
		//adjust position
		mPosition.y -= mJumpForce * deltaTime;

		//reduce jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}
	else if (!mJumping)
	{
		mCanJump = true;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			return;
		case SDLK_RIGHT:
			mMovingRight = true;
			return;
			break;
		}
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			return;
		case SDLK_RIGHT:
			mMovingRight = false;
			return;
		case SDLK_SPACE:
			Character::Jump();
			return;
			break;
		}
		break;
	}
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= MovementSpeed * deltaTime;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += MovementSpeed * deltaTime;
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

Character::~Character()
{
	mRenderer = NULL;
}