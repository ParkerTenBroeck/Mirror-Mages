#include "game.h"

#include "ECS/components/components.h"
#include "scene/Scene.h"

bool Game::init() {
	scene = new Scene();
	scene->OnStart(nullptr);
	return true;
}

bool Game::onUserUpdate(float fElapsedTime, olc::PixelGameEngine* context) {
	scene->OnUpdate(fElapsedTime, context);
	return true;
}