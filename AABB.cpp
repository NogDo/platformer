#include "AABB.h"

AABB::AABB() {
	this->LeftTop = Vector(0.0f, 0.0f);
	this->RightBottom = Vector(0.0f, 0.0f);
}

AABB::AABB(Vector leftTop, Vector rightBottom) {
	this->LeftTop = leftTop;
	this->RightBottom = rightBottom;
}

AABB::AABB(float leftTopX, float leftTopY, float rightBottomX, float rightBottomY) {
	this->LeftTop.x = leftTopX;
	this->LeftTop.y = leftTopY;
	this->RightBottom.x = rightBottomX;
	this->RightBottom.y = rightBottomY;
}