#pragma once
#include "MirrorMages.h"



int main()
{
	MirrorMages mirrorMage;
	if (mirrorMage.Construct(256, 240, 4, 4))
	if (mirrorMage.Construct(256, 144, 5, 5, false, true))
		mirrorMage.Start();

	return 0;
}