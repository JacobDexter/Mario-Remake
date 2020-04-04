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
protected:
	//drawing
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	//movement
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	FACING mFacingDirection;

	//character state
	CHARACTER_STATE characterState;

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
	bool isJumping() { return mJumping; };
	void CancelJump() { mJumpForce = 0.0f; };
	void SetPosition(Vector2D newPosition);
	void PlayerDeath(float deltaTime);

	//character state
	void SetState(CHARACTER_STATE state);
	int GetState();

	//character collisions
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	bool CheckViewportCollision();

	//movement variables
	bool mMovingLeft;
	bool mMovingRight;

	//Level Map
	LevelMap* mCurrentLevelMap;
};

#endif