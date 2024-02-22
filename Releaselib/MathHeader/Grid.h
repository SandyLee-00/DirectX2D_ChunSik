#pragma once
#include "headers.h"
#include "Vector2.h"

namespace Grid
{
	const int maxx = 1920;
	const int maxy = 1080;

	const int minx = 0;
	const int miny = 120;

	const Vector2 size = {96, 96};

	Vector2 GetPostion(int _x, int _y);
}