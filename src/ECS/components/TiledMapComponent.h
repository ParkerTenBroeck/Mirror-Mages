#pragma once
#include "common.h"


struct Tile {
	olc::vf2d offset;
	olc::vi2d sourceOffset;
	olc::vf2d scale;
	bool flippedH;
	bool flippedV;
};

struct TiledMapComponent {
	olc::Sprite* sprite = nullptr;
	olc::Decal* decal = nullptr;

	olc::vi2d tilePixelSize = {8,8};

	olc::vi2d tilesXY = {0,0};
	static const int maxTiles = 256;
	Tile tileSet[maxTiles];

	uint8_t layer = 0;
	uint8_t* tileMap = nullptr;

	TiledMapComponent(const char* name, uint8_t _layer) {
		sprite = new olc::Sprite(name);
		decal = new olc::Decal(sprite);
		this->layer = _layer;

		this->tilesXY = {128,32};
		tileMap = new uint8_t[tilesXY.x * tilesXY.y];
	}

	~TiledMapComponent() {
		delete(tileMap);
	}
};