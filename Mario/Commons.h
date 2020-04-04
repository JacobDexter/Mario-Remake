#pragma once

struct Vector2D
{
	float x;
	float y;


	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float x, y;

	float width, height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;

		width = initialWidth;
		height = initialHeight;
	}
};

enum SCREENS
{
	SCREEN_MENU = 0,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_LEADERBOARD
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum CHARACTER_STATE
{
	CHARACTERSTATE_DEAD = 0,
	CHARACTERSTATE_ALIVE
};