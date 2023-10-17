#pragma once

#include "Graphics.h"
#include "Vector.h"

class AABB {
public:
	Vector LeftTop;
	Vector RightBottom;

	AABB();
	AABB(Vector leftTop, Vector rightBottom);
	AABB(float leftTopX, float leftTopY, float rightBottomX, float rightBottomY);
};