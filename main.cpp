#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include "Mario/mario.h"
#include "Mario/Texture2D.h"
#include "Mario/Commons.h"
#include "Mario/Constants.h"
#include "Mario/GameScreenManager.h"

using namespace std;

SDL_Window* gameWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Music* gMusic = NULL;
GameScreenManager* gameScreenManager;

Uint32 gOldTime;

int main(int argc, char* args[])
{
	//SDL Initiation check
	if (InitSDL())
	{
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		gOldTime = SDL_GetTicks();
		bool quit = false;

		LoadMusic("Music/Mario.ogg");

		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}

		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	
	//Close Window
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//create window
		gameWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	}

	if (gameWindow != NULL && gRenderer != NULL)
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}
		else
		{
			return true;
		}
	}
}

void CloseSDL()
{
	//free up memory after the game is finished using the window
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;

	//clean up gameScreenManager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e; //event handler
	SDL_PollEvent(&e); // find occured events
	
	switch (e.type)
	{
		case SDL_QUIT:
			return true;
		case SDL_KEYUP:
			switch(e.key.keysym.sym)
				case SDLK_q:
					return true;
				break;
		break;
	}
	
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	gOldTime = newTime;

	return false;
}

void Render()
{
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//update screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}
