#pragma once

#include "Vector.h"
#include "AABB.h"
#include "Graphics.h"
#include "SpriteSheet.h"

class Bullet{
	Vector LeftTop;
	Vector RightBottom;
	AABB aabb;
	Graphics* gfx;

	SpriteSheet* sprite_Bullet;

public:
	static const int nBulletSize = 3;
	static const int nBossBulletSize = 10;
	Vector velocity;
	float maxSpeed;

	void Init(float x, float y, Graphics* gfx, bool isBoss);
	void DrawBullet(bool isBoss);
	void MoveBullet(double timeDelta);
	AABB GetAABB();
};