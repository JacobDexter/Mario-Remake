#pragma once

#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"
#include "Texture2D.h"

using namespace std;

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	//behaviour
	void TakeDamage();
	void Jump();

private:
	//sprite
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	//behaviour
	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;

	void FlipRightWayUp();
};

#endif