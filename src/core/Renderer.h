#pragma once
#include "extern/olc/include/olcPixelGameEngine.h"

namespace Renderer
{
	void init(olc::PixelGameEngine*);

	int ScreenWidth();
	int ScreenHeight();

	void DrawPartialDecal(olc::vf2d pos, olc::vf2d size, olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint = olc::WHITE);

	void DrawPartialRotatedDecal(olc::vf2d pos, olc::Decal* decal, const float fAngle, olc::vf2d center, olc::vf2d source_pos, olc::vf2d source_size, olc::vf2d scale = { (1.0f),(1.0f) }, const olc::Pixel tint = olc::WHITE);
}
