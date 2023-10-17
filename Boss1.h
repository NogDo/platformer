#pragma once

#include <math.h>
#include <vector>
#include "Enemy.h"
#include "Bullet.h"
#include "Graphics.h"

class Boss1 : public Enemy {
	float fMovePower;

	bool isDown;

	Graphics* gfx;
public:
	static const int nBossSpriteSizeX = 371;
	static const int nBossSpriteSizeY = 401;
	static const int nBossSizeX = 100;
	static const int nBossSizeY = 100;

	Bullet b1;
	std::vector<Bullet> bullets;

	void Init(Graphics* gfx) override;
	void Load() override;
	void UnLoad() override;
	void GetHit() override;
	void Attack(Vector aimDirNorm) override;

	float GetPositionX();
	float GetPositionY();
	float GetHP();
	float GetMaxHP();

	AABB GetAABB();

	void Move(double timeDelta);
	void MoveUp(double timeDelta);
	void MoveDown(double timeDelta);
	
	void DrawHPBar();
};