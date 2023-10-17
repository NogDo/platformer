#include <iostream>
#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"
#include "Level0.h"

void Level1::Load() {
	sprites = new SpriteSheet(L"Images//CharacterIdle.png", gfx, character.nCharacterSpritesWidth, character.nCharacterSpritesHeight);
	sprites_Idle = new SpriteSheet(L"Images//CharacterIdle.png", gfx, character.nCharacterSpritesWidth, character.nCharacterSpritesHeight);
	sprites_Move = new SpriteSheet(L"Images//CharacterWalk.png", gfx, character.nCharacterSpritesWidth, character.nCharacterSpritesHeight);
	sprites_Jump = new SpriteSheet(L"Images//CharacterJump.png", gfx, character.nCharacterSpritesWidth, character.nCharacterSpritesHeight);
	sprites_SandMap = new SpriteSheet(L"Images//SandMap.png", gfx, map.GetTileWidth(), map.GetTileHeight());
	sprites_Boss = new SpriteSheet(L"Images//Boss.png", gfx, boss.nBossSpriteSizeX, boss.nBossSpriteSizeY);

	animation = Ani_Idle;

	horizontalPower = 0.0f;
	verticalPower = 0.0f;
	MovePower = 150.0f;
	gravity = 300.0f;
	jumpPower = 750.0f;
	nowJumpPower = jumpPower;
	fBossAttackTimer = 0.0f;
	fBossSpecialAttackTimer = 0.0f;
	fBossSpecialAttackTimer2 = 0.0f;
	fCharacterAttackTimer = 0.0f;

	nIdleLeftCount = 5;
	nIdleRightCount = 0;
	nIdleNowCount = nIdleRightCount;
	nMoveLeftCount = 4;
	nMoveRightCount = 0;
	nMoveNowCount = nMoveRightCount;
	nJumpLeftCount = 1;
	nJumpRightCount = 0;
	nJumpNowCount = nJumpRightCount;
	nJumpCount = 0;
	nBossSpecialAttack2Count = 0;

	character.Init(gfx);
	boss.Init(gfx);
	map.Init();
}

void Level1::Unload() {
	delete sprites_Idle;
	delete sprites_Move;
	delete sprites_Jump;
	delete sprites_SandMap;
	delete sprites_Boss;
}

void Level1::Update(double timeTotal, double timeDelta) {
	// 중력 작용
	character.Gravity(gravity, timeDelta);

	// 캐릭터 점프
	if (isJump) {
		character.Jump(nowJumpPower, timeDelta);
		nowJumpPower -= 15.0f;
		if (nowJumpPower <= 0.0f) {
			nowJumpPower = 0.0f;
		}
	}

	// 캐릭터 좌우
	if (isPressLeftKey) {
		character.MoveLeft(horizontalPower, timeDelta);
	}
	else if (isPressRightKey) {
		character.MoveRight(horizontalPower, timeDelta);
	}

	// 타일 충돌
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (map.sand[i][j] != -1) {
				if (collision.CheckCollision(character.GetAABBFoot(), map.tile[i][j].GetAABB())) { // 캐릭터 발&타일 충돌체크
					character.SetPositionY(map.tile[i][j].GetPosition().y - character.nCharacterColliderHeight - 10);
					if (isJump) {
						isJump = false;
						nJumpCount = 0;
						nowJumpPower = jumpPower;
						if (isPressLeftKey || isPressRightKey) {
							SetSpriteMove();
							animation = Ani_Move;
						}
						else {
							SetSpriteIdle();
							animation = Ani_Idle;
						}
					}
				}

				if (collision.CheckCollision(character.GetAABBRoot(), map.tile[i][j].GetAABB())) { // 캐릭터 머리&타일 충돌판정
					character.SetPositionY(map.tile[i][j].GetPosition().y + character.nCharacterColliderHeight);
					if (isJump) {
						isJump = false;
						nowJumpPower = jumpPower;
						if (isPressLeftKey || isPressRightKey) {
							SetSpriteMove();
							animation = Ani_Move;
						}
						else {
							SetSpriteIdle();
							animation = Ani_Idle;
						}
					}
				}

				if (collision.CheckCollision(character.GetAABBLeft(), map.tile[i][j].GetAABB())) { // 캐릭터 왼쪽&타일 충돌판정
					character.SetPositionX(map.tile[i][j].GetPosition().x + character.nCharacterColliderWidth - 5);
				}

				if (collision.CheckCollision(character.GetAABBRight(), map.tile[i][j].GetAABB())) { // 캐릭터 오른쪽&타일 충돌판정
					character.SetPositionX(map.tile[i][j].GetPosition().x - character.nCharacterColliderWidth);
				}

				for (int w = 0; w < character.bullets.size(); w++) { // 캐릭터 총알&타일 충돌체크
					if (collision.CheckCollision(character.bullets[w].GetAABB(), map.tile[i][j].GetAABB())) {
						character.bullets.erase(character.bullets.begin() + w);
					}
				}

				for (int w = 0; w < boss.bullets.size(); w++) { // 보스 총알&타일 충돌체크
					if (collision.CheckCollision(boss.bullets[w].GetAABB(), map.tile[i][j].GetAABB())) {
						boss.bullets.erase(boss.bullets.begin() + w);
					}
				}
			}
		}
	}

	if (boss.GetHP() > 0.0f) {
		//std::cout << boss.GetHP() << "\n";
		// 보스 이동
		boss.Move(timeDelta);

		// 보스 공격 패턴
		if ((boss.GetHP() / boss.GetMaxHP() * 100) >= 80.0f) {
			fBossAttackTimer += timeDelta;
			if (fBossAttackTimer >= 0.5f) {
				Vector playerPosition = Vector(character.GetPositionX() + character.nCharacterColliderWidth / 2, character.GetPositionY() + character.nCharacterColliderHeight / 2);
				aimDir = playerPosition - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);
				fBossAttackTimer -= 0.5f;
			}
		}
		else if ((boss.GetHP() / boss.GetMaxHP() * 100) >= 60.0f) {
			fBossAttackTimer += timeDelta;
			if (fBossAttackTimer >= 0.4f) {
				Vector playerPosition1 = Vector(character.GetPositionX(), character.GetPositionY());
				aimDir = playerPosition1 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				Vector playerPosition2 = Vector(character.GetPositionX() + character.nCharacterColliderWidth, character.GetPositionY() + character.nCharacterColliderHeight);
				aimDir = playerPosition2 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				fBossAttackTimer -= 0.4f;
			}
		}
		else if ((boss.GetHP() / boss.GetMaxHP() * 100) >= 40.0f) {
			fBossAttackTimer += timeDelta;
			if (fBossAttackTimer >= 0.4f) {
				Vector playerPosition1 = Vector(character.GetPositionX(), character.GetPositionY());
				aimDir = playerPosition1 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				Vector playerPosition2 = Vector(character.GetPositionX() + character.nCharacterColliderWidth, character.GetPositionY() + character.nCharacterColliderHeight);
				aimDir = playerPosition2 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				fBossAttackTimer -= 0.4f;
			}

			fBossSpecialAttackTimer += timeDelta;
			if (fBossSpecialAttackTimer >= 3.0f) {
				for (int i = 0; i < 720; i += 40) {
					Vector position = Vector(0, i);
					aimDir = position - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
					aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
					boss.Attack(aimDirNorm);
				}

				fBossSpecialAttackTimer -= 3.0f;
			}
		}
		else if ((boss.GetHP() / boss.GetMaxHP() * 100) >= 1.0f) {
			fBossAttackTimer += timeDelta;
			if (fBossAttackTimer >= 0.4f) {
				Vector playerPosition1 = Vector(character.GetPositionX(), character.GetPositionY());
				aimDir = playerPosition1 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				Vector playerPosition2 = Vector(character.GetPositionX() + character.nCharacterColliderWidth, character.GetPositionY() + character.nCharacterColliderHeight);
				aimDir = playerPosition2 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				Vector playerPosition3 = Vector(character.GetPositionX() + character.nCharacterColliderWidth / 2, character.GetPositionY() + character.nCharacterColliderHeight / 2);
				aimDir = playerPosition3 - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
				aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
				boss.Attack(aimDirNorm);

				fBossAttackTimer -= 0.4f;
			}

			fBossSpecialAttackTimer += timeDelta;
			if (fBossSpecialAttackTimer >= 3.0f) {
				fBossSpecialAttackTimer2 += timeDelta;
				if (fBossSpecialAttackTimer2 >= 0.25f && nBossSpecialAttack2Count <= 2) {
					for (int i = 0; i < 720; i += 60) {
						Vector position = Vector(0, i);
						aimDir = position - Vector(boss.GetPositionX() + boss.nBossSizeX / 2, boss.GetPositionY() + boss.nBossSizeY / 2);
						aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
						boss.Attack(aimDirNorm);
					}
					fBossSpecialAttackTimer2 -= 0.25f;
					nBossSpecialAttack2Count++;
				}
			}

			if (fBossSpecialAttackTimer >= 5.0f) {
				fBossSpecialAttackTimer -= 5.0f;
				fBossSpecialAttackTimer2 = 0.0f;
				nBossSpecialAttack2Count = 0;
			}
		}


		// 보스 총알 이동
		for (int i = 0; i < boss.bullets.size(); i++) {
			boss.bullets[i].MoveBullet(timeDelta);

			if (boss.bullets[i].GetAABB().LeftTop.x < 0 || boss.bullets[i].GetAABB().LeftTop.x > 1280 ||
				boss.bullets[i].GetAABB().LeftTop.y < 0 || boss.bullets[i].GetAABB().LeftTop.y > 720) {
				boss.bullets.erase(boss.bullets.begin() + i);
			}
		}

		// 보스 총알 충돌
		for (int i = 0; i < boss.bullets.size(); i++) {
			if (collision.CheckCollision(boss.bullets[i].GetAABB(), character.GetAABB())) { // 캐릭터
				boss.bullets.erase(boss.bullets.begin() + i);
				character.GetHit();

				if (character.GetCharacterHP() <= 0.0f) {
					this->Unload();
					GameController::LoadInitialLevel(new Level0());
				}
			}
		}
	}

	// 캐릭터 총알 발사
	fCharacterAttackTimer += timeDelta;
	if (fCharacterAttackTimer >= 0.15f) {
		if (isMousePress) {
			POINT point;
			if (GetCursorPos(&point)) {
				ScreenToClient(hwnd, &point);
				mousePosition = Vector(point.x, point.y);
			}

			aimDir = mousePosition - Vector(character.GetPositionX() + character.nCharacterColliderWidth / 2, character.GetPositionY() + character.nCharacterColliderHeight / 2);
			aimDirNorm = aimDir.Divide(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
			//std::cout << aimDirNorm.x << ", " << aimDirNorm.y << "\n";
			//std::cout << character.bullets.size() << "\n";

			character.Shooting(aimDirNorm);
			fCharacterAttackTimer = 0.0f;
		}
	}

	// 캐릭터 총알 이동
	for (int i = 0; i < character.bullets.size(); i++) {
		character.bullets[i].MoveBullet(timeDelta);

		if (character.bullets[i].GetAABB().LeftTop.x < 0 || character.bullets[i].GetAABB().LeftTop.x > 1280 ||
			character.bullets[i].GetAABB().LeftTop.y < 0 || character.bullets[i].GetAABB().LeftTop.y > 720) {
			character.bullets.erase(character.bullets.begin() + i);
		}
	}

	// 캐릭터 총알 & 적 충돌체크
	for (int i = 0; i < character.bullets.size(); i++) {
		if (collision.CheckCollision(character.bullets[i].GetAABB(), boss.GetAABB())) { // 보스 충돌
			character.bullets.erase(character.bullets.begin() + i);
			boss.GetHit();
		}
	}

	

	frame += 1;
	if (frame >= INT_MAX - 1) {
		frame = 0;
	}
}

void Level1::Render() {
	gfx->ClearScreen(1.0f, 1.0f, 1.0f);

	// 맵 그리기
	DrawMap();

	// 캐릭터 애니메이션
	switch (animation)
	{
	case Ani_Idle:
		sprites->Draw((frame / 7) % 5 + nIdleNowCount, character.GetPositionX(), character.GetPositionY());
		break;

	case Ani_Move:
		sprites->Draw((frame / 12) % 4 + nMoveNowCount, character.GetPositionX(), character.GetPositionY());
		break;

	case Ani_Jump:
		sprites->Draw(nJumpNowCount, character.GetPositionX(), character.GetPositionY());
		break;

	default:
		break;
	}

	// 캐릭터 Collision
	//gfx->DrawRectangle(character.GetAABB().LeftTop.x, character.GetAABB().LeftTop.y, character.GetAABB().RightBottom.x, character.GetAABB().RightBottom.y);
	//gfx->DrawRectangle(character.GetAABBFoot().LeftTop.x, character.GetAABBFoot().LeftTop.y, character.GetAABBFoot().RightBottom.x, character.GetAABBFoot().RightBottom.y);
	//gfx->DrawRectangle(character.GetAABBLeft().LeftTop.x, character.GetAABBLeft().LeftTop.y, character.GetAABBLeft().RightBottom.x, character.GetAABBLeft().RightBottom.y);
	//gfx->DrawRectangle(character.GetAABBRight().LeftTop.x, character.GetAABBRight().LeftTop.y, character.GetAABBRight().RightBottom.x, character.GetAABBRight().RightBottom.y);
	//gfx->DrawRectangle(character.GetAABBRoot().LeftTop.x, character.GetAABBRoot().LeftTop.y, character.GetAABBRoot().RightBottom.x, character.GetAABBRoot().RightBottom.y);

	// 캐릭터 총알 그리기
	for (int i = 0; i < character.bullets.size(); i++) {
		character.bullets[i].DrawBullet(false);
	}

	// 캐릭터 체력바 그리기
	character.DrawHpBar();

	if (boss.GetHP() > 0.0f) {
		// 보스 그리기
		sprites_Boss->Draw(0, boss.GetPositionX(), boss.GetPositionY(), boss.nBossSizeX, boss.nBossSizeY);

		// 보스 HP바 그리기
		boss.DrawHPBar();

		// 보스 총알 그리기
		for (int i = 0; i < boss.bullets.size(); i++) {
			boss.bullets[i].DrawBullet(true);
		}
	}
}

void Level1::MoveUp() {
	isPressUpKey = true;

	verticalPower = -MovePower;
}

void Level1::Jump() {
	if (nJumpCount < 2) {
		nowJumpPower = jumpPower;
	}
	isJump = true;
	nJumpCount++;

	SetSpriteJump();
	animation = Ani_Jump;
}

void Level1::MoveDown() {
	isPressDownKey = true;

	verticalPower = MovePower;
}

void Level1::MoveLeft() {
	isPressLeftKey = true;

	horizontalPower = -MovePower;

	nIdleNowCount = nIdleLeftCount;
	nMoveNowCount = nMoveLeftCount;
	nJumpNowCount = nJumpLeftCount;

	SetSpriteMove();
	animation = Ani_Move;
}

void Level1::MoveRight() {
	isPressRightKey = true;

	horizontalPower = MovePower;

	nIdleNowCount = nIdleRightCount;
	nMoveNowCount = nMoveRightCount;
	nJumpNowCount = nJumpRightCount;

	SetSpriteMove();
	animation = Ani_Move;
}

void Level1::StopUp() {
	isPressUpKey = false;
	if (isPressDownKey) {
		verticalPower = MovePower;
	}
}

void Level1::StopDown() {
	isPressDownKey = false;
	if (isPressUpKey) {
		verticalPower = -MovePower;
	}
}

void Level1::StopLeft() {
	isPressLeftKey = false;
	if (isPressRightKey) {
		horizontalPower = MovePower;
	}
	else {
		SetSpriteIdle();
		animation = Ani_Idle;
	}
}

void Level1::StopRight() {
	isPressRightKey = false;
	if (isPressLeftKey) {
		horizontalPower = -MovePower;
	}
	else {
		SetSpriteIdle();
		animation = Ani_Idle;
	}
}

void Level1::SetSpriteMove() {
	sprites = sprites_Move;
}

void Level1::SetSpriteIdle() {
	sprites = sprites_Idle;
}

void Level1::SetSpriteJump() {
	sprites = sprites_Jump;
}

void Level1::DrawMap() {
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (map.sand[i][j] != -1) {
				sprites_SandMap->Draw(map.sand[i][j], map.GetTileWidth() * j, map.GetTileHeight() * i);
			}
		}
	}
}

void Level1::MouseDown(HWND hwnd) {
	this->hwnd = hwnd;
	isMousePress = true;
}

void Level1::MouseUp() {
	isMousePress = false;
}
