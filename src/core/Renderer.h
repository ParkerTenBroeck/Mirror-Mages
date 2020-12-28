#pragma once
#include "extern/olc/include/olcPixelGameEngine.h"

namespace Renderer
{
	void init(olc::PixelGameEngine*);

	int ScreenWidth();
	int ScreenHeight();

	void DrawPartialDecal(olc::vf2d pos, olc::vf2d size, olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint = olc::WHITE);

	void DrawPartialRotatedDecal(olc::vf2d pos, olc::Decal* decal, const float fAngle, olc::vf2d center, olc::vf2d source_pos, olc::vf2d source_size, olc::vf2d scale = { (1.0f),(1.0f) }, const olc::Pixel tint = olc::WHITE);

	void DrawDecal(olc::vf2d source, olc::vf2d size, olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint = olc::WHITE, bool flipH = false, bool flipV = false, float fAngleCenter = 0.0f, float fAnglePoint = 0.0f, olc::vf2d rotPoint = { (0.0f), (0.0f) });

	void DrawPartialWarpedDecal(olc::Decal* decal, olc::vf2d(&points)[4], olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint = olc::WHITE);

	void SetTargetLayer();

	olc::vf2d RotatePoint(olc::vf2d p, olc::vf2d o, float fAngle);

	olc::vf2d RotatePoint(olc::vf2d p, olc::vf2d o, float s, float c);

	void DrawString(olc::vi2d pos, const std::string& message, olc::Pixel col = olc::WHITE, float scale = 1.0f);

	void Clear(olc::Pixel color);

	void SetDebugLayer();
	void SetBackgroundLayer();
}
