#include "Entity.h"

Entity::Entity(entt::entity handle, Scene* scene) {
	this->m_EntityHandle = handle;
	this->m_Scene = scene;
}