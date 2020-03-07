#pragma once

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 412

using namespace std;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();