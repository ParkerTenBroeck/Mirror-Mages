#pragma once
#include "extern/olc/include/olcPixelGameEngine.h"

namespace Input
{
	void init(olc::PixelGameEngine*);

	bool IsKeyPressed(olc::Key);
	bool IsKeyHeld(olc::Key);
	bool IsKeyRelesed(olc::Key);

	bool IsMouseButtonPressed(uint32_t);
	bool IsMouseButtonHeld(uint32_t);
	bool IsMouseButtonRelesed(uint32_t);

	int32_t GetMouseWheel();
	int32_t GetMouseX();
	int32_t GetMouseY();
}