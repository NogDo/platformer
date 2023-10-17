#pragma once

#include "Graphics.h"
#include "Vector.h"
#include "AABB.h"

class Tile {
	Vector LeftTop;
	Vector RightBottom;
	Vector Position;
	AABB aabb;

public:
	static const int tileSizeWidth = 40;
	static const int tileSizeHeight = 40;

	void Init(bool isEmpty, int row, int column);
	Vector GetPosition();
	AABB GetAABB();
};