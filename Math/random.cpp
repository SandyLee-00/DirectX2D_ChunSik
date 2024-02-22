#include "random.h"

Vector2 random::GetRandom(const Vector2& _min, const Vector2& _max)
{
	int x = GetRandom<int>((int)_min.x, (int)_max.x);
	int y = GetRandom<int>((int)_min.y, (int)_max.x);

	return { x, y };
}
