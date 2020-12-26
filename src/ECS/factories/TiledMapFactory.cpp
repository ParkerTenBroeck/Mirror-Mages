#include "TiledMapFactory.h"
#include "ECS/components/components.h"

namespace TiledMapFactory {

	Entity MakeTiledMap(const char* name, IScene* scene, uint8_t layer) {
		Entity e = scene->CreateEntity();

		e.AddComponent<TiledMapComponent>("Scene1", layer);
		
		return e;
	}

}