#pragma once

#ifndef _CHARACTERENEMY_H
#define _CHARACTERENEMY_H

#include "Character.h"
#include "Texture2D.h"
#include "SoundEffect.h"

class CharacterEnemy : public Character
{
public:
	CharacterEnemy(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterEnemy();

	void Jump();
};

#endif