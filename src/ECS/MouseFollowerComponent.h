#pragma once

#include "ECS\ECS.h"
#include "ECS\Components.h"
#include "LightningBold.h"

class MouseFollowerComponent : public EntityComponent {
private:
	SpriteComponent* sprite;
	TransformComponent* pos;

	int circleSize = 1;
	int followDistance = 8;

public:

	MouseFollowerComponent(int _circleSize = 1, int _followDistance = -1) {
		this->circleSize = _circleSize;
		this->followDistance = _followDistance;
	}

	void onUserUpdate(float elapsedTime, olc::PixelGameEngine* context) {
		olc::vf2d mouse = { (float)context->GetMouseX(), (float)context->GetMouseY() };

		{ //draws mouse thing?????
			olc::vf2d t = { mouse.x - (pos->x() + sprite->getWidth() / 2), mouse.y - (pos->y() + sprite->getHeight() / 2) };
			float temp = (1 / sqrt(t.x * t.x + t.y * t.y)) * followDistance;
			t = { t.x * temp + pos->x() + 3.5f, t.y * temp + pos->y() + 3.5f };
			context->FillCircle(t, 1, olc::WHITE);

			//SetLayerScale(lightningLayer, 5.0, 0.5);
			//SetDrawTarget(decorationLayer);
			//Clear(olc::BLANK);
			//FillCircle({ 128, 72 }, 4, olc::GREY);
			static LightningBolt* bolt = nullptr;
			if (bolt) {
				bolt->draw(context);
				if (bolt->update(elapsedTime)) {
					delete bolt;
					bolt = nullptr;
				}
			}
			else {
				if (context->GetMouse(0).bPressed) {
					bolt = new LightningBolt(t, mouse, 7.0, olc::Pixel(125, 249, 255, 255), 0.1);
				}
			}
		}
	}

	void init() override {
		this->sprite = &entity->getComponent<SpriteComponent>();
		this->pos = &entity->getComponent<TransformComponent>();
		if (this->followDistance < 0) {
			followDistance = sqrt(sprite->getWidth() * sprite->getWidth() / 2 + sprite->getHeight() * sprite->getHeight() / 2) + 0.99f;
		}
	}
};