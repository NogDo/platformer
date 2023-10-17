#pragma once

#include <math.h>
#include <vector>
#include "Graphics.h"
#include "Bullet.h"

class Character {
	float hp;
	float maxHp;

	float fPositionX;
	float fPositionY;
	Vector LeftTop;
	Vector RightBottom;

	AABB aabb;
	AABB aabbFoot;
	AABB aabbLeft;
	AABB aabbRight;
	AABB aabbRoot;

	Graphics* gfx;
public:
	static const int nCharacterSpritesWidth = 50;
	static const int nCharacterSpritesHeight = 60;
	static const int nCharacterColliderWidth = 40;
	static const int nCharacterColliderHeight = 50;

	Bullet b1;
	std::vector<Bullet> bullets;
	int nBulletCount;

	void Init(Graphics* gfx);
	void MoveLeft(float movePower, double timeDelta);
	void MoveRight(float movePower, double timeDelta);
	void Jump(float jumpPower, double timeDelta);
	void Gravity(float gravityPower, double timeDelta);

	float GetPositionX();
	float GetPositionY();
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPosition(float x, float y);

	AABB GetAABB();
	AABB GetAABBFoot();
	AABB GetAABBLeft();
	AABB GetAABBRight();
	AABB GetAABBRoot();

	void Shooting(Vector aimDirNorm);

	void GetHit();
	float GetCharacterHP();
	void DrawHpBar();
};