#pragma once
#include "common.h"
#include "core/game/scene/IScene.h"

namespace TiledMapFactory {

	Entity MakeTiledMap(const char*, IScene* scene, uint8_t layer);

}