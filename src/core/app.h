#pragma once
#include "game/game.h"

class App : public olc::PixelGameEngine
{
private:
	Game game;

public:
	App();

public:


	bool OnUserCreate() override;


	bool OnUserUpdate(float fElapsedTime) override;
};

