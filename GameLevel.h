#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include "Vector.h"

class GameLevel {
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphcis) {
		gfx = graphcis;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void MoveUp() = 0;
	virtual void MoveDown() = 0;
	virtual void MoveRight() = 0;
	virtual void MoveLeft() = 0;
	virtual void StopUp() = 0;
	virtual void StopDown() = 0;
	virtual void StopRight() = 0;
	virtual void StopLeft() = 0;
	virtual void SetSpriteMove() = 0;
	virtual void SetSpriteIdle() = 0;
	virtual void SetSpriteJump() = 0;
	virtual void Jump() = 0;
	virtual void DrawMap() = 0;
	virtual void MouseDown(HWND point) = 0;
	virtual void MouseUp() = 0;
};