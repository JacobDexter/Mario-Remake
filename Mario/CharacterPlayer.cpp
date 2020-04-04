#include "CharacterPlayer.h"

CharacterPlayer::CharacterPlayer(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	sJump = new SoundEffect(1, "Sounds/Jump.wav", 0);
}

CharacterPlayer::~CharacterPlayer()
{

}

void CharacterPlayer::Jump()
{
	if (mCanJump)
	{
		sJump->Play();
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}