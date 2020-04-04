#pragma once

#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include "SDL.h"
#include "Commons.h"
#include "Mario.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "SoundEffect.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	virtual void Render();

	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); };
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; };
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;

	//sound effects
	SoundEffect* sPow;
};

#endif // _POWBLOCK_H