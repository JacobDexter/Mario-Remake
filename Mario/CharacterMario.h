#pragma once

#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"

using namespace std;

class CharacterMario : public Character
{
public:
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // _CHARACTERMARIO_H