#include "IScene.h"
#include "Entity.h"

const Entity IScene::CreateEntity() {
	Entity entity = { m_Registry.create(), this };
	return entity;
}