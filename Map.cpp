#include "Map.h"

void Map::Init() {
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (sand[i][j] != -1) {
				tile[i][j].Init(false, i, j);
			}
			else {
				tile[i][j].Init(true, i, j);
			}
		}
	}
}

int Map::GetTileWidth() {
	return tile[0][0].tileSizeWidth;
}

int Map::GetTileHeight() {
	return tile[0][0].tileSizeHeight;
}