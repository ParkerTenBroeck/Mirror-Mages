#pragma once


struct CameraComponent {
	bool Primary = true;
	olc::vf2d size = {1.0f, 1.0f};
	olc::vf2d scale = {1.0f, 1.0f};

	olc::vf2d maxBounds = {0,0};
	olc::vf2d minBounds = {0,0};

	olc::vf2d offset = {0,0};
	float fAngleOffset = 0.0f;
};