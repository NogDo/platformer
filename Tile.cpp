#include "Tile.h"

void Tile::Init(bool isEmpty, int row, int column) {
	if (!isEmpty) {
		/*LeftTop = Vector(column * tileSizeWidth - tileSizeWidth / 2, row * tileSizeHeight - tileSizeHeight / 2);
		RightBottom = Vector(column * tileSizeWidth + tileSizeWidth / 2, row * tileSizeHeight + tileSizeHeight / 2);*/
		LeftTop = Vector(column * tileSizeWidth, row * tileSizeHeight);
		RightBottom = Vector(column * tileSizeWidth + tileSizeWidth, row * tileSizeHeight + tileSizeHeight);
		Position = Vector(column * tileSizeWidth, row * tileSizeHeight);
		aabb = AABB(LeftTop, RightBottom);
	}
	else {
		LeftTop = Vector();
		RightBottom = Vector();
		Position = Vector();
		aabb = AABB();
	}
}

Vector Tile::GetPosition() {
	return Position;
}

AABB Tile::GetAABB() {
	return this->aabb;
}