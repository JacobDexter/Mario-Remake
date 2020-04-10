#pragma once

#include "SDL.h"
#include <vector>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "LevelMap.h"
#include "SoundEffect.h"
#include "Text.h"
#include "GameScreenManager.h"
#include "Music.h"
#include <fstream>

class Texture2D;
class PowBlock;
class Character;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	//Updates
	void UpdatePOWBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	bool InsertScoreIntoLeaderboard(int score, string path);

	//Enemies
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position, FACING direction, float speed);
	void SpawnRandomEnemy(Vector2D position, FACING direction);

private:
	//variables
	Texture2D* mBackgroundTexture;
	Character* gCharacterMario;
	Character* gCharacterLuigi;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	//Level Setup
	bool SetUpLevel();
	void SetLevelMap();

	//Screen Shake
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	void ScreenShake();

	//sound effects
	Music* gBackgroundMusic;
	SoundEffect* sKoopaSpawn;
	SoundEffect* sGameOver;
	SoundEffect* sPlayerDeath;
	SoundEffect* sKoopaKick;

	//Koopas
	vector<CharacterKoopa*> mKoopas;
	float enemyRespawnTimer = ENEMY_RESPAWN_TIME;

	//Coins
	vector<CharacterCoin*> mCoins;

	//Text
	//SCORE TEXT
	Text* scoreboard;
	TTF_Font* marioFont;
	SDL_Texture* scoreTexture;
	SDL_Rect scoreRect;
	SDL_Surface* scoreSurface;

	//SCORE NUMBER
	Text* scoreNum;
	SDL_Texture* scoreNumTexture;
	SDL_Rect scoreNumRect;
	SDL_Surface* scoreNumSurface;
	void UpdateScoreText(int score);

	bool gameOver;
};