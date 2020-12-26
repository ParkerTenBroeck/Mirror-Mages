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

	uint8_t backgroundLayer;
	uint8_t tileLayer;
	uint8_t decorationLayer;
	uint8_t lightningLayer;
	uint8_t entityLayer;
	uint8_t effectLayer;

public:
	App();

public:


	bool OnUserCreate() override;


	bool OnUserUpdate(float fElapsedTime) override;
};

