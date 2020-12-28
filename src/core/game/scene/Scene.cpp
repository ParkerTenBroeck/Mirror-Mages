#include "Scene.h"
#include "ECS/components/Components.h"
#include "ECS/factories/Factories.h"
#include "ECS/systems/Systems.h"

#include "util/random.h"

//Scene::~Scene()
//{
	//idk how to clean up ;(
//}

//int entities = 0;

bool Scene::OnStart() {
	Entity e = PlayerFactory::MakePlayer(this, 0);
	//entities++;
	return true;
}

bool Scene::OnStop() {
	return true;
}

bool Scene::OnUpdate(float fElapsedTime) {

	if (Input::IsKeyHeld(olc::Key::P)) {
		for (int i = 0; i < 100; i++) {
			Entity e = PlayerFactory::MakeEnemy(this);
			e.GetComponent<TransformComponent>().location = {RandomRange(0.0f, 256.0f), RandomRange(0.0f,144.0f)};
			//entities++;
		}
	}

	NativeScriptingSystem::OnUpdate(this, fElapsedTime);

	//Rendering
	Rendering2DSystem::OnUpdate(this);

	return true;
}