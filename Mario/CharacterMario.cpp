#include "CharacterMario.h"
#include <iostream>

using namespace std;

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : CharacterPlayer(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_LEFT;
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

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
		case SDLK_UP:
			CharacterPlayer::Jump();
			return;
			break;
		}
		break;
	}
}