#pragma once

#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H

#include "SDL_mixer.h"
#include <iostream>

using namespace std;

class SoundEffect
{
public:
	//constructor/destructor
	SoundEffect(int channel, string path, int looping);
	~SoundEffect();

	//functions
	void Play();
	void Load();

private:
	int sChannel;
	string sPath;
	int sLooping;
};

#endif