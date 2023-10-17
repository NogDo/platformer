#include "Bullet.h"

void Bullet::Init(float x, float y, Graphics* gfx, bool isBoss) {
	if (isBoss) {
		LeftTop = Vector(x + 1, y + 1);
		RightBottom = Vector(x + nBossBulletSize - 1, y + nBossBulletSize - 1);
		maxSpeed = 5.0f;
	}
	else {
		LeftTop = Vector(x, y);
		RightBottom = Vector(x + nBulletSize, y + nBulletSize);
		maxSpeed = 10.0f;
	}

	aabb = AABB(LeftTop, RightBottom);
	velocity = Vector(0, 0);


	this->gfx = gfx;
	sprite_Bullet = new SpriteSheet(L"Images//BossBullet.png", this->gfx, 496, 465);
}

void Bullet::DrawBullet(bool isBoss) {
	if (isBoss) {
		sprite_Bullet->Draw(0, LeftTop.x, LeftTop.y, nBossBulletSize, nBossBulletSize);
	}
	else {
		gfx->DrawRectangle(LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y);
	}
}

void Bullet::MoveBullet(double timeDelta) {
	LeftTop += velocity;
	RightBottom += velocity;
	aabb.LeftTop += velocity;
	aabb.RightBottom += velocity;
}

AABB Bullet::GetAABB() {
	return this->aabb;
}