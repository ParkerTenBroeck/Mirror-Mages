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

	bool OnStart();
	bool OnUpdate(float fElapsedTime);
	bool OnStop();
	//temp

};