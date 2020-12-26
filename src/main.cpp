#pragma once
#define OLC_PGE_APPLICATION
#include "core/app.h"

int main()
{
	
	App app;
	if (app.Construct(256, 240, 4, 4))
	if (app.Construct(256, 144, 5, 5, false, true))
		app.Start();

	return 0;
} 