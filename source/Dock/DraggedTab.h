#pragma once

#include "Tab.h"

struct DraggedTab
{
	int x, y, width, height;

	bool showArea;
	int areaX, areaY, areaWidth, areaHeight;
	
	Tab* tab;
};