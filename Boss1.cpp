#include "Boss1.h"

void Boss1::Init(Graphics* gfx){
	hp = 100.0f;
	MaxHp = hp;

	fPositionX = 1100.0f;
	fPositionY = 100.0f;

	aabb = AABB(fPositionX, fPositionY, fPositionX + nBossSizeX, fPositionY + nBossSizeY);

	fMovePower = 200.0f;

	isDown = true;

	this->gfx = gfx;
	b1.Init(fPositionX, fPositionY, gfx, true);
}

void Boss1::Load(){
	
}

void Boss1::UnLoad(){

}

void Boss1::GetHit(){
	hp -= 1.0f;
}

void Boss1::Attack(Vector aimDirNorm){
	b1.Init(fPositionX + nBossSizeX / 2, fPositionY + nBossSizeY / 2, gfx, true);
	b1.velocity = aimDirNorm.Multyply(b1.maxSpeed);
	bullets.push_back(b1);
}

float Boss1::GetPositionX(){
	return fPositionX;
}

float Boss1::GetPositionY(){
	return fPositionY;
}

float Boss1::GetHP()
{
	return hp;
}

float Boss1::GetMaxHP()
{
	return MaxHp;
}

AABB Boss1::GetAABB(){
	return aabb;
}

void Boss1::Move(double timeDelta){
	if (fPositionY <= 100.0f) {
		isDown = true;
	}
	else if(fPositionY >= 600.0f){
		isDown = false;
	}

	if (isDown) {
		MoveDown(timeDelta);
	}
	else {
		MoveUp(timeDelta);
	}
}

void Boss1::MoveUp(double timeDelta){
	fPositionY -= fMovePower * timeDelta;
	aabb.LeftTop.y -= fMovePower * timeDelta;
	aabb.RightBottom.y -= fMovePower * timeDelta;
}

void Boss1::MoveDown(double timeDelta){
	fPositionY += fMovePower * timeDelta;
	aabb.LeftTop.y += fMovePower * timeDelta;
	aabb.RightBottom.y += fMovePower * timeDelta;
}

void Boss1::DrawHPBar(){
	gfx->DrawRectangle(fPositionX - 10, fPositionY - 20,
		fPositionX + (nBossSizeX * hp / MaxHp) - 10, fPositionY - 10,
		200, 0, 0);
}

