#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
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

	//character state
	characterState = CHARACTERSTATE_ALIVE;

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

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
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

bool Character::CheckViewportCollision()
{
	// Right Border
	if (mPosition.x + mTexture->GetWidth() > SCREEN_WIDTH + mTexture->GetWidth()) {
		mPosition.x = 32 - mTexture->GetWidth();
		return true;
	}
	// Left Border
	else if (mPosition.x + mTexture->GetWidth() < 0) {
		mPosition.x = SCREEN_WIDTH - mTexture->GetWidth();
		return true;
	}
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

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void Character::SetState(CHARACTER_STATE state)
{
	characterState = state;
}

int Character::GetState()
{
	return (int)characterState;
}

void Character::PlayerDeath(float deltaTime)
{
	mPosition.y += (GRAVITY * 4) * deltaTime;
}

Character::~Character()
{
	mRenderer = NULL;
}