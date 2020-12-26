#include "game.h"

#include "ECS/components/components.h"
#include "scene/Scene.h"

bool Game::init() {
	scene = new Scene();
	scene->OnStart();
	return true;
}

bool Game::OnUpdate(float fElapsedTime) {
	scene->OnUpdate(fElapsedTime);
	return true;
}