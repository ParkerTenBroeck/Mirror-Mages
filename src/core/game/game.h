#pragma once
//#include "exter"
#include "scene/IScene.h"
#include "common.h"

class Game {
public:
	bool init();
	bool OnUpdate(float fElapstedTime);

private:
//	bool logic(float fElapstedTime);
//	bool render(olc::PixelGameEngine* context);
	IScene* scene;
};