#pragma once

#include "extern/entt/include/entt.hpp"
#include "IScene.h"

class Entity {

public:
	Entity() = default;
	Entity(entt::entity handle, IScene* scene);
	Entity(const Entity& other) = default;

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		if (HasComponent <T>()) {
			//error???
		}
		return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		return m_Scene->m_Registry.get<T>(m_EntityHandle);
	}

	template<typename T>
	bool HasComponent()
	{
		return m_Scene->m_Registry.has<T>(m_EntityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		m_Scene->m_Registry.remove<T>(m_EntityHandle);
	}

	operator bool() const { return m_EntityHandle != entt::null; }
private:
	entt::entity m_EntityHandle{ entt::null };
	IScene* m_Scene;
};
