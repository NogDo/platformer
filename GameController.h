#pragma once

#include "GameLevel.h"
#include "Graphics.h"
#include "HPTimer.h"
#include <conio.h>

class GameController {
	GameController() { }

	static GameLevel* currentLevel;
	static GameLevel* prevLevel;

	static HPTimer* hpTimer;

public:
	static bool Loading;

	static void Init();

	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);

	static void Render();
	static void Update();
	
	static GameLevel* GetCurrentLevel();
	static GameLevel* GetPrevLevel();
};
