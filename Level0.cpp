#include <iostream>
#include "Level0.h"
#include "GameController.h"

void Level0::Load() {
	sprite_StartButton  = new SpriteSheet(L"Images//StartButton.png", gfx, 1271, 401);
	startButtonPosition = Vector(515, 320);
	startButtonSizeX = 250.0f;
	startButtonSizeY = 80.0f;
	startButton = AABB(startButtonPosition.x, startButtonPosition.y, startButtonPosition.x + startButtonSizeX, startButtonPosition.y + startButtonSizeY);

	level1 = new Level1();
}

void Level0::Unload() {
	delete sprite_StartButton;
}

void Level0::Render() {
	gfx->ClearScreen(1.0f, 1.0f, 1.0f);

	sprite_StartButton->Draw(0, startButtonPosition.x, startButtonPosition.y, startButtonSizeX, startButtonSizeY);
}

void Level0::Update(double timeTotal, double timeDelta) {

}

void Level0::MoveUp(){
}

void Level0::MoveDown(){
}

void Level0::MoveLeft(){
}

void Level0::MoveRight(){
}

void Level0::StopUp(){
}

void Level0::StopDown(){
}

void Level0::StopRight(){
}

void Level0::StopLeft(){
}

void Level0::SetSpriteMove(){
}

void Level0::SetSpriteIdle(){
}

void Level0::SetSpriteJump(){
}

void Level0::Jump(){
}

void Level0::DrawMap(){
}

void Level0::MouseDown(HWND point) {
	this->hwnd = point;
	CheckPressStartButton();
}

void Level0::MouseUp(){
}

void Level0::CheckPressStartButton(){
	POINT point;
	if (GetCursorPos(&point)) {
		ScreenToClient(hwnd, &point);

		if (point.x >= startButton.LeftTop.x && point.x <= startButton.RightBottom.x && point.y >= startButton.LeftTop.y && point.y <= startButton.RightBottom.y) {
			GameController::SwitchLevel(level1);
		}
	}
}
