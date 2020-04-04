#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Mario/mario.h"
#include "Mario/Texture2D.h"
#include "Mario/Commons.h"
#include "Mario/Constants.h"
#include "Mario/GameScreenManager.h"

using namespace std;

SDL_Window* gameWindow = NULL;
SDL_Renderer* gRenderer = NULL;
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

	TTF_Init();

	if (gameWindow != NULL && gRenderer != NULL)
	{
		//opens mixer audio channelsfor use
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

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Update()
{
	//poll users keyboard and mouse events
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e; //event handler
	SDL_PollEvent(&e); // find occured events
	
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
	break;
	}

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
