#pragma once


struct CameraComponent {
	bool Primary = true;
	olc::vf2d size;
	olc::vf2d maxBounds = {0,0};
	olc::vf2d minBounds = {0,0};
};