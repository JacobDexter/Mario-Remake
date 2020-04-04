#include "CharacterEnemy.h"

CharacterEnemy::CharacterEnemy(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{

}

CharacterEnemy::~CharacterEnemy()
{

}

void CharacterEnemy::Jump()
{
	if (mCanJump)
	{
		mJumpForce = 250.0f;
		mJumping = true;
		mCanJump = false;
	}
}