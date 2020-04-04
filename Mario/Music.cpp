#include "Music.h"

Music::Music()
{
	gMusic = NULL;
}

Music::~Music()
{
	//Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
}

void Music::LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}
}

void Music::Pause()
{
	Mix_PauseMusic();
}

void Music::Resume()
{
	Mix_ResumeMusic();
}

void Music::Stop()
{
	Mix_HaltMusic();
}