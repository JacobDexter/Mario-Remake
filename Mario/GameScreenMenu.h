#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include "SoundEffect.h"
#include <vector>

class Texture2D;
class PowBlock;
class Character;

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	//Blocks
	void UpdatePOWBlock();

	//Enemies
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

private:
	//variables
	Texture2D* mBackgroundTexture;
	Character* gCharacterMario;
	Character* gCharacterLuigi;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	//functions
	bool SetUpLevel();
	void SetLevelMap();

	//Screen Shake
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	void ScreenShake();

	//sound effects
	SoundEffect* mGunShot;

	//Enemies
	vector<CharacterKoopa*> mEnemies;
	float koopaRespawnTimer = KOOPA_RESPAWN_TIME;
};