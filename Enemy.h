#pragma once

#include "AABB.h"
#include "Vector.h"

class Enemy {
protected:
	float hp;
	float MaxHp;
	float fPositionX;
	float fPositionY;

	AABB aabb;

public:
	virtual void Init(Graphics* gfx) = 0;
	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void GetHit() = 0;
	virtual void Attack(Vector aimDirNorm) = 0;
};