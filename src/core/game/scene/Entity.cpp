#include "Entity.h"

Entity::Entity(entt::entity handle, IScene* scene) {
	this->m_EntityHandle = handle;
	this->m_Scene = scene;
}