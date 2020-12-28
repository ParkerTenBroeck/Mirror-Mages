#include "Random.h"
#include<cstdlib>

float RandomRange(float min, float max) //range : [min, max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}