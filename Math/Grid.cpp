#include "Grid.h"

Vector2 Grid::GetPostion(int _x, int _y)
{
	float x = _x * size.x;
	float y = _y * size.y;

	return Vector2{x + minx, y + miny};
}
