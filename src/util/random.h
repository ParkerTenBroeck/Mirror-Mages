#pragma once

#include<math.h>
#pragma once
float random(float min, float max) //range : [min, max)
{
	float r = (double)rand() / (double)RAND_MAX;
	return min + r * (max - min);
}