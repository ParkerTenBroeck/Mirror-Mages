#pragma once
#include "entt/include/entt.hpp"
#include "olc/include/olcPixelGameEngine.h"
//#include "Entity.h"

class Entity;

class IScene
{
public:
	virtual ~IScene() = default;
	virtual bool OnStart() { return true; };
	virtual bool OnUpdate(float fElapsedTime) { return true; };
	virtual bool OnStop() { return true; };

	const Entity CreateEntity();

	entt::registry m_Registry;
};