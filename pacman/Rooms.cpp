#include "Rooms.h"
#include <cmath>
#include <iostream>
Rooms::Rooms()
{
}

Rooms::Rooms(int X, int Y, int h, int w)
{
	starX = X;
	starY = Y;
	hight = h;
	wight = w;
	centerx = starX +  wight / 2;
	centery = starY + hight / 2;
}
