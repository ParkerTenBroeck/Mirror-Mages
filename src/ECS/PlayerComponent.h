#pragma once

#include "ECS\ECS.h"
#include "ECS\Components.h"

class PlayerComponent : public EntityComponent {
private:
	SpriteComponent* sprite;
	TransformComponent* pos;

public:
	const int speed = 50;

	void onUserUpdate(float elapsedTime, olc::PixelGameEngine* context) override {

		{
			static float timeCounter = 0;

			static int counter = 0;
			if (counter >= 23) {
				counter = 0;
			}
			if (timeCounter > 0.1) {
				counter++;
				timeCounter = 0;
			}
			timeCounter += elapsedTime;

			this->sprite->setSpriteOrigin({ (counter % 14) * 9, (counter / 14) * 9 });
		}
		{
			if (context->GetKey(olc::S).bHeld) {
				pos->yChange(elapsedTime * speed);
			}
			if (context->GetKey(olc::W).bHeld) {
				pos->yChange(-elapsedTime * speed);
			}
			if (context->GetKey(olc::D).bHeld) {
				pos->xChange(elapsedTime * speed);
			}
			if (context->GetKey(olc::A).bHeld) {
				pos->xChange(-elapsedTime * speed);
			}
		}


		
	}

	void init() override {
		this->sprite = &entity->getComponent<SpriteComponent>();
		this->sprite->setSpriteSize({8,8});
		this->pos = &entity->getComponent<TransformComponent>();
	}
};