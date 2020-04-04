#include "CharacterLuigi.h"
#include <iostream>

using namespace std;

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : CharacterPlayer(renderer, imagePath, startPosition, map)
{

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			return;
		case SDLK_d:
			mMovingRight = true;
			return;
			break;
		}
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			return;
		case SDLK_d:
			mMovingRight = false;
			return;
		case SDLK_w:
			CharacterPlayer::Jump();
			return;
			break;
		}
		break;
	}
}
