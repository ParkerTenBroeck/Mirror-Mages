#pragma once
#include "extern/olc/include/olcPixelGameEngine.h"

struct SpriteComponent {
	olc::Sprite* sprite = nullptr;
	olc::Decal* decal = nullptr;;
	bool useDecal = false;
	olc::vi2d origin = {0,0};
	olc::vi2d size = {0,0};
	olc::Pixel tint = olc::WHITE;
	bool flippedH = false;
	bool flippedV = false;

	SpriteComponent() {

	}
	SpriteComponent(const char* _path, float _useDecal, int _orgX = 0, int _orgY = 0, int _sizeX = -1, int _sizeY = -1) {
		this->sprite = new olc::Sprite(_path);
		if (_useDecal) {
			this->decal = new olc::Decal(this->sprite);
		}
		this->useDecal = _useDecal;
		this->origin = {_orgX, _orgY};
		if(_sizeX < 0 || _sizeY < 0){
			this->size = {sprite->width - _orgX, sprite->height - _orgY};
		}
		else {
			this->size = {_sizeX, _sizeY};
		}
	}

	SpriteComponent(olc::Decal* _decal, int _orgX = 0, int _orgY = 0, int _sizeX = -1, int _sizeY = -1) {
		this->decal = _decal;
		this->sprite = _decal->sprite;
		this->useDecal = true;
		this->origin = { _orgX, _orgY };
		if (_sizeX < 0 || _sizeY < 0) {
			this->size = { sprite->width - _orgX, sprite->height - _orgY };
		}
		else {
			this->size = { _sizeX, _sizeY };
		}
	}
};