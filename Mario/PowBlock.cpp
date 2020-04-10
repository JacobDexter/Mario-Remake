#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	mRenderer = renderer;

	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(mRenderer);
	
	mTexture->LoadFromFile(imagePath.c_str());

	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);

	sPow = new SoundEffect(1, "Sounds/Pow.wav", 0);
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		//Sets portion of spritesheet to render
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		//Draw Texture
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;
	sPow->Play();

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}