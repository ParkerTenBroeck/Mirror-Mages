#pragma once
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