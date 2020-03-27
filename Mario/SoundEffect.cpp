#include "SoundEffect.h"

using namespace std;

Mix_Chunk* gSoundEffect = NULL;

SoundEffect::SoundEffect(int channel, string path, int looping)
{
	sChannel = channel;
	sPath = path;
	sLooping = looping;
}

void SoundEffect::Play()
{
	Load();
	Mix_PlayChannel(sChannel, gSoundEffect, sLooping);
}

void SoundEffect::Load()
{
	gSoundEffect = Mix_LoadWAV(sPath.c_str());

	if (gSoundEffect == NULL)
	{
		cout << "Failed to load sound effect! Error: " << Mix_GetError() << endl;
	}
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(gSoundEffect);
	gSoundEffect = NULL;
}