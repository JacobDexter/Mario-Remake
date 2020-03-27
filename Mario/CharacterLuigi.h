#pragma once

#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"
#include "Texture2D.h"
#include "SoundEffect.h"

using namespace std;

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // _CHARACTERLUIGI_H