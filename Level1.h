#pragma once

#include "GameLevel.h"
#include "Character.h"
#include "Map.h"
#include "Boss1.h"
#include "Collision.h"

enum CharacterAnmation {
	Ani_Idle,
	Ani_Move,
	Ani_Jump,
	Ani_None
};

class Level1 : public GameLevel {
	float horizontalPower;
	float verticalPower;
	float MovePower;
	float gravity;
	float jumpPower;
	float nowJumpPower;
	float fBossAttackTimer;
	float fBossSpecialAttackTimer;
	float fBossSpecialAttackTimer2;
	float fCharacterAttackTimer;

	int frame;
	int nIdleLeftCount;
	int nIdleRightCount;
	int nIdleNowCount;
	int nMoveLeftCount;
	int nMoveRightCount;
	int nMoveNowCount;
	int nJumpLeftCount;
	int nJumpRightCount;
	int nJumpNowCount;
	int nJumpCount;
	int nBossSpecialAttack2Count;

	bool isPressLeftKey;
	bool isPressRightKey;
	bool isPressUpKey;
	bool isPressDownKey;
	bool isJump; 
	bool isMousePress;

	SpriteSheet* sprites;
	SpriteSheet* sprites_Idle;
	SpriteSheet* sprites_Move;
	SpriteSheet* sprites_Jump;
	SpriteSheet* sprites_SandMap;
	SpriteSheet* sprites_Boss;

	CharacterAnmation animation;
	Character character;

	Boss1 boss;

	Map map;

	Collision collision;

	Vector mousePosition;
	Vector aimDir;
	Vector aimDirNorm;

	HWND hwnd;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void MoveUp() override;
	void MoveDown() override;
	void MoveLeft() override;
	void MoveRight() override;
	void StopUp() override;
	void StopDown() override;
	void StopRight() override;
	void StopLeft() override;
	void SetSpriteMove() override;
	void SetSpriteIdle() override;
	void SetSpriteJump() override;
	void Jump() override;
	void DrawMap() override;
	void MouseDown(HWND point) override;
	void MouseUp() override;
};