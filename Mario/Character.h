#pragma once

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"

using namespace std;

class Texture2D;

class Character
{
private:
	//movement
	FACING mFacingDirection;

protected:
	//drawing
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	//movement
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	float mCollisionRadius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	
	//character movement
	void AddGravity(float deltaTime);
	void Jump();
	void SetPosition(Vector2D newPosition);

	//character collisions
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	//movement variables
	bool mMovingLeft;
	bool mMovingRight;

	//Level Map
	LevelMap* mCurrentLevelMap;
};

#endif // _CHARACTER_H