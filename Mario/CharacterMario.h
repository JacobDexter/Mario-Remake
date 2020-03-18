#pragma once

#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "Texture2D.h"

using namespace std;

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // _CHARACTERMARIO_H