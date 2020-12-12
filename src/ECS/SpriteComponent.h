#pragma once


#include "ECS\ECS.h"
#include "ECS\Components.h"

class SpriteComponent : public EntityComponent {
private:
	TransformComponent* position;
	olc::Sprite* sprite;

	olc::vi2d spriteOrigin;
	olc::vi2d spriteSize;

	uint32_t scale = 1;
	bool flipped = false;
public:

	SpriteComponent(olc::Sprite* _sprite, olc::vi2d _spriteOrigin = { 0,0 }, olc::vi2d _spriteSize = {-1,-1}, uint32_t _scale = 1, bool _flipped = false) {
		this->sprite = _sprite;
		this->spriteOrigin = _spriteOrigin;
		if (_spriteSize.x < 0 || _spriteSize.y < 0) {
			this->spriteSize = {sprite->width, sprite->height};
		}
		this->scale = _scale;
		this->flipped = _flipped;
	}
	void onUserUpdate(float elapsedTime, olc::PixelGameEngine* context) override {
		context->DrawPartialSprite({ (int)position->x(), (int)position->y() }, sprite, { 0, 0 }, { 8, 8 }, scale,flipped);
	}
	void init() override {
		position = &entity->getComponent<TransformComponent>();
	}

	void setSprite(olc::Sprite* _sprite) {
		this->sprite = _sprite;
	}

	int getRealWidth() {
		return sprite->width;
	}
	int getWidth() {
		return spriteSize.x;
	}
	int getRealHeight() {
		return sprite->height;
	}
	int getHeight() {
		return spriteSize.y;
	}

	void setSpriteSize(olc::vi2d size) {
		this->spriteSize = size;
	}

	void setSpriteOrigin(olc::vi2d origin) {
		this->spriteOrigin = origin;
	}
	void setScale(uint32_t _scale) {
		this->scale = _scale;
	}
	void setFlipped(bool _flipped) {
		this->flipped = _flipped;
	}
};