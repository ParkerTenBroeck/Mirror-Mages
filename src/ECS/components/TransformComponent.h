#pragma once

struct TransformComponent {
	olc::vf2d location = {0.0f, 0.0f};
	float rot = 0;
	olc::vf2d scale = { 1.0f, 1.0f };

	TransformComponent() = default;
};