#include "Scene.h"
#include "ECS/components/Components.h"
#include "ECS/factories/Factories.h"
#include "ECS/systems/Systems.h"

#include "util/random.h"

//Scene::~Scene()
//{
	//idk how to clean up ;(
//}


bool Scene::OnStart() {
	Entity e = PlayerFactory::MakePlayer(this, 0);
	e.AddComponent<CameraComponent>();
	return true;
}

bool Scene::OnStop() {
	return true;
}

bool Scene::OnUpdate(float fElapsedTime) {

	if (Input::IsKeyHeld(olc::Key::E)) {
		static int count = 1;
		for (int i = 0; i < 100; i++) {
			Entity e = PlayerFactory::MakeEnemy(this);
			e.GetComponent<TransformComponent>().location = {random(0.0f, 256.0f), random(0.0f,144.0f)};
			count++;
		}
	}

	NativeScriptingSystem::OnUpdate(this, fElapsedTime);

	//Rendering
	Rendering2DSystem::OnUpdate(this);

	return true;
}