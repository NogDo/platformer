#include "Character.h"
#include <iostream>

void Character::Init(Graphics* gfx) {
	hp = 20.0f;
	maxHp = hp;

	fPositionX = 100.0f;
	fPositionY = 0.0f;

	LeftTop = Vector(fPositionX + 5, fPositionY + 10);
	RightBottom = Vector(fPositionX + nCharacterColliderWidth, fPositionY + nCharacterColliderHeight);
	aabb = AABB(LeftTop, RightBottom);
	aabbFoot = AABB(LeftTop.x + 5, RightBottom.y + 7, RightBottom.x - 5, RightBottom.y + 10);
	aabbLeft = AABB(LeftTop.x, LeftTop.y + 3, LeftTop.x + 5 , RightBottom.y - 3);
	aabbRight = AABB(RightBottom.x - 5, LeftTop.y + 3, RightBottom.x, RightBottom.y - 3);
	aabbRoot = AABB(LeftTop.x + 5, LeftTop.y - 5, RightBottom.x - 5, LeftTop.y);

	this->gfx = gfx;
	b1.Init(fPositionX, fPositionY, gfx, false);
	nBulletCount = 0;
}

void Character::MoveLeft(float movePower, double timeDelta) {
	fPositionX += movePower * timeDelta;
	aabb.LeftTop.x += movePower * timeDelta;
	aabb.RightBottom.x += movePower * timeDelta;

	aabbFoot.LeftTop.x += movePower * timeDelta;
	aabbFoot.RightBottom.x += movePower * timeDelta;

	aabbLeft.LeftTop.x += movePower * timeDelta;
	aabbLeft.RightBottom.x += movePower * timeDelta;

	aabbRight.LeftTop.x += movePower * timeDelta;
	aabbRight.RightBottom.x += movePower * timeDelta;

	aabbRoot.LeftTop.x += movePower * timeDelta;
	aabbRoot.RightBottom.x += movePower * timeDelta;
}

void Character::MoveRight(float movePower, double timeDelta) {
	fPositionX += movePower * timeDelta;
	aabb.LeftTop.x += movePower * timeDelta;
	aabb.RightBottom.x += movePower * timeDelta;

	aabbFoot.LeftTop.x += movePower * timeDelta;
	aabbFoot.RightBottom.x += movePower * timeDelta;

	aabbLeft.LeftTop.x += movePower * timeDelta;
	aabbLeft.RightBottom.x += movePower * timeDelta;

	aabbRight.LeftTop.x += movePower * timeDelta;
	aabbRight.RightBottom.x += movePower * timeDelta;

	aabbRoot.LeftTop.x += movePower * timeDelta;
	aabbRoot.RightBottom.x += movePower * timeDelta;
}

void Character::Jump(float jumpPower, double timeDelta) {
	fPositionY -= jumpPower * timeDelta;
	aabb.LeftTop.y -= jumpPower * timeDelta;
	aabb.RightBottom.y -= jumpPower * timeDelta;

	aabbFoot.LeftTop.y -= jumpPower * timeDelta;
	aabbFoot.RightBottom.y -= jumpPower * timeDelta;

	aabbLeft.LeftTop.y -= jumpPower * timeDelta;
	aabbLeft.RightBottom.y -= jumpPower * timeDelta;

	aabbRight.LeftTop.y -= jumpPower * timeDelta;
	aabbRight.RightBottom.y -= jumpPower * timeDelta;

	aabbRoot.LeftTop.y -= jumpPower * timeDelta;
	aabbRoot.RightBottom.y -= jumpPower * timeDelta;
}

void Character::Gravity(float gravityPower, double timeDelta) {
	fPositionY += gravityPower * timeDelta;
	aabb.LeftTop.y += gravityPower * timeDelta;
	aabb.RightBottom.y += gravityPower * timeDelta;

	aabbFoot.LeftTop.y += gravityPower * timeDelta;
	aabbFoot.RightBottom.y += gravityPower * timeDelta;

	aabbLeft.LeftTop.y += gravityPower * timeDelta;
	aabbLeft.RightBottom.y += gravityPower * timeDelta;

	aabbRight.LeftTop.y += gravityPower * timeDelta;
	aabbRight.RightBottom.y += gravityPower * timeDelta;

	aabbRoot.LeftTop.y += gravityPower * timeDelta;
	aabbRoot.RightBottom.y += gravityPower * timeDelta;
}

float Character::GetPositionX() {
	return fPositionX;
}

float Character::GetPositionY() {
	return fPositionY;
}

void Character::SetPositionX(float x) {
	//std::cout << "posX: " << fPositionX << "\n";
	//std::cout << "x: " << x << "\n";
	fPositionX = x;
	aabb.LeftTop.x = x + 5;
	aabb.RightBottom.x = x + nCharacterColliderWidth;

	aabbFoot.LeftTop.x = aabb.LeftTop.x + 5;
	aabbFoot.RightBottom.x = aabb.RightBottom.x - 5;

	aabbLeft.LeftTop.x = aabb.LeftTop.x;
	aabbLeft.RightBottom.x = aabb.LeftTop.x + 5;

	aabbRight.LeftTop.x = aabb.RightBottom.x - 5;
	aabbRight.RightBottom.x = aabb.RightBottom.x;

	aabbRoot.LeftTop.x = aabb.LeftTop.x + 5;
	aabbRoot.RightBottom.x = aabb.RightBottom.x - 5;
}

void Character::SetPositionY(float y) {
	fPositionY = y;
	aabb.LeftTop.y = y + 3;
	aabb.RightBottom.y = y + nCharacterColliderHeight;

	aabbFoot.LeftTop.y = aabb.RightBottom.y + 7;
	aabbFoot.RightBottom.y = aabb.RightBottom.y + 10;

	aabbLeft.LeftTop.y = aabb.LeftTop.y + 3;
	aabbLeft.RightBottom.y = aabb.RightBottom.y - 3;

	aabbRight.LeftTop.y = aabb.LeftTop.y + 3;
	aabbRight.RightBottom.y = aabb.RightBottom.y - 3;

	aabbRoot.LeftTop.y = aabb.LeftTop.y - 5;
	aabbRoot.RightBottom.y = aabb.LeftTop.y;
}

void Character::SetPosition(float x, float y) {
	fPositionX = x;
	fPositionY = y;

	aabb.LeftTop.x = x;
	aabb.LeftTop.y = y;
	aabb.RightBottom.x = x + nCharacterColliderWidth;
	aabb.RightBottom.y = y + nCharacterColliderHeight;

	aabbFoot.LeftTop.x = aabb.LeftTop.x;
	aabbFoot.RightBottom.x = aabb.LeftTop.x + 5;
	aabbFoot.LeftTop.y = aabb.RightBottom.y + 7;
	aabbFoot.RightBottom.y = aabb.RightBottom.y + 10;

	aabbLeft.LeftTop.x = aabb.LeftTop.x;
	aabbLeft.RightBottom.x = aabb.LeftTop.x + 5;
	aabbLeft.LeftTop.y = aabb.LeftTop.y + 3;
	aabbLeft.RightBottom.y = aabb.RightBottom.y - 3;

	aabbRight.LeftTop.x = aabb.RightBottom.x - 5;
	aabbRight.RightBottom.x = aabb.RightBottom.x;
	aabbRight.LeftTop.y = aabb.LeftTop.y + 3;
	aabbRight.RightBottom.y = aabb.RightBottom.y - 3;

	aabbRoot.LeftTop.x = aabb.LeftTop.x + 5;
	aabbRoot.RightBottom.x = aabb.RightBottom.x - 5;
	aabbRoot.LeftTop.y = aabb.LeftTop.y - 5;
	aabbRoot.RightBottom.y = aabb.LeftTop.y;
}

AABB Character::GetAABB() {
	return this->aabb;
}

AABB Character::GetAABBFoot() {
	return this->aabbFoot;
}

AABB Character::GetAABBLeft()
{
	return this->aabbLeft;
}

AABB Character::GetAABBRight() {
	return this->aabbRight;
}

AABB Character::GetAABBRoot() {
	return this->aabbRoot;
}

void Character::Shooting(Vector aimDirNorm) {
	b1.Init(fPositionX + nCharacterColliderWidth / 2, fPositionY + nCharacterColliderHeight / 2, gfx, false);
	b1.velocity = aimDirNorm.Multyply(b1.maxSpeed);
	bullets.push_back(b1);
}

void Character::GetHit(){
	hp -= 1.0f;
}

float Character::GetCharacterHP(){
	return hp;
}

void Character::DrawHpBar(){
	gfx->DrawRectangle(fPositionX, fPositionY - 10, 
		fPositionX + (nCharacterSpritesWidth * hp / maxHp), fPositionY, 
		200, 0, 0);
}
