#pragma once

#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"

using namespace std;

class CharacterLuigi : public Character
{
public:
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // _CHARACTERLUIGI_H