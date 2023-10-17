#pragma once

#include <Wincodec.h>
#include "Graphics.h"

class SpriteSheet {
	Graphics* gfx;
	ID2D1Bitmap* bmp;
	int spriteWidth, spriteHeight;
	int spriteAccross;

public:
	// Constructor
	SpriteSheet(const wchar_t* filename, Graphics* gfx);
	SpriteSheet(const wchar_t* filename, Graphics* gfx, int spriteWidth, int spriteHeight);
	
	// Destructor
	~SpriteSheet();

	// ºñÆ®¸ÊÀ» ·»´õÅ¸°Ù¿¡ ±×¸²
	void Draw();
	void Draw(int index, float x, float y);
	void Draw(int index, float positionX, float positionY, float sizeX, float sizeY);

	int GetSpriteWidth();
	int GetSpriteHeight();
};