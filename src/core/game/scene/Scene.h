#pragma once
#include "extern/entt/include/entt.hpp"
////#include "common.h"
#include "IScene.h"

class Entity;

class Scene : public IScene
{
public:
	//Scene();
	//virtual ~Scene();

	bool OnStart(olc::PixelGameEngine* context);
	bool OnUpdate(float fElapsedTime, olc::PixelGameEngine* context);
	bool OnStop();
	//temp
	Entity CreateEntity();

	//entt::registry& Reg() { return m_Registry; }

	entt::registry m_Registry;

};