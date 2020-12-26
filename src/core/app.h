#pragma once
#include "extern/olc/include/olcPixelGameEngine.h"
#include "game/game.h"
//#include "../../extern/olc/include/olcPixelGameEngine.h"

class App : public olc::PixelGameEngine
{
private:

	//Scene scene;

//	olc::Sprite* characterSpriteSheet = nullptr;

//	olc::Sprite* levelSprite = nullptr;
//	olc::Decal* levelDecal = nullptr;
	Game game;

public:
	App();

public:


	bool OnUserCreate() override;


	bool OnUserUpdate(float fElapsedTime) override;
};

