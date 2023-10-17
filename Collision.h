#pragma once
#include "Graphics.h"
#include "AABB.h"

class Collision {
public:
	bool CheckCollision(AABB aabb1, AABB aabb2);
};