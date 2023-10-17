#include "Collision.h"

bool Collision::CheckCollision(AABB aabb1, AABB aabb2) {
	if (aabb1.RightBottom.x < aabb2.LeftTop.x || aabb1.LeftTop.x > aabb2.RightBottom.x) {
		return false;
	}

	if (aabb1.RightBottom.y < aabb2.LeftTop.y || aabb1.LeftTop.y > aabb2.RightBottom.y) {
		return false;
	}
	/*bool point1 = (aabb1.RightBottom.x < aabb2.LeftTop.x || aabb1.LeftTop.x > aabb2.RightBottom.x);
	bool point2 = (aabb1.RightBottom.y < aabb2.LeftTop.y || aabb1.LeftTop.y > aabb2.RightBottom.y);*/

	return true;
}