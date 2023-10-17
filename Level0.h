#pragma once

#include "Level1.h"
#include "GameLevel.h"
#include "Character.h"
#include "Map.h"
#include "Collision.h"

class Level0 : public GameLevel {
	HWND hwnd;

	SpriteSheet* sprite_StartButton;
	Vector startButtonPosition;
	AABB startButton;
	float startButtonSizeX;
	float startButtonSizeY;
	
	Level1* level1;
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

	void CheckPressStartButton();
};