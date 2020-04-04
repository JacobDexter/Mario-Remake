#pragma once

#ifndef _MUSIC_H
#define _MUSIC_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

class Music
{
public:
	Music();
	~Music();

	void LoadMusic(string path);
	void Pause();
	void Resume();
	void Stop();
private:
	Mix_Music* gMusic;
};

#endif