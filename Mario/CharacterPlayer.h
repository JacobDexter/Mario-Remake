#pragma once

#ifndef _CHARACTERPLAYER_H
#define _CHARACTERPLAYER_H

#include "Character.h"
#include "Texture2D.h"
#include "SoundEffect.h"

class CharacterPlayer : public Character
{
public:
	CharacterPlayer(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterPlayer();

	//character movement
	void Jump();

private:
	SoundEffect* sJump;
};

#endif