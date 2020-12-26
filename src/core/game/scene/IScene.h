#pragma once
#include "entt/include/entt.hpp"
#include "olc/include/olcPixelGameEngine.h"

class IScene
{
public:
	virtual ~IScene() = default;
	virtual bool OnStart(olc::PixelGameEngine* context) { return true; };
	virtual bool OnUpdate(float fElapsedTime, olc::PixelGameEngine* context) { return true; };
	virtual bool OnStop() { return true; };


};