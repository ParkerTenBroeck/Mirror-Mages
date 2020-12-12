#pragma once

#include "ECS\ECS.h"

class TransformComponent : public EntityComponent {
private:
	float xPos;
	float yPos;
	float rotation;
public:
	inline float x() { return xPos; }
	inline float y() { return yPos; }
	inline void x(float x) { xPos = x; }
	inline void y(float y) { yPos = y; }
	inline void xChange(float x) { xPos += x; }
	inline void yChange(float y) { yPos += y; }
	inline void setPos(float x, float y) { xPos = x; yPos = y; }
};