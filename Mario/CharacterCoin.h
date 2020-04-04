#pragma once

#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

using namespace std;

#include "CharacterEnemy.h"
#include "Texture2D.h"
#include "SoundEffect.h"

class CharacterCoin : public CharacterEnemy
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	//behaviour
	void CollectCoin();
	void SetCollected(bool state);
	bool GetCollected();
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

private:
	//sprite
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	//sprite animation
	int spritePortion;
	float spriteChangeTimer;
	int spriteOrigin;
	float spriteInterval;

	//behaviour
	float mMovementSpeed;
	bool mCoinCollected;

	//sounds
	SoundEffect* sCoinCollect;
};

#endif