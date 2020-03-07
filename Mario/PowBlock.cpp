#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);

	if (!mTexture->LoadFromFile(imagePath.c_str()));
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
}

void PowBlock::Render()
{

}

void PowBlock::TakeAHit()
{

}

PowBlock::~PowBlock()
{

}