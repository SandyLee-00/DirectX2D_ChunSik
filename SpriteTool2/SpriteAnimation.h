#pragma once

#include <string>
#include <vector>

class ExtractedSprite;

class SpriteAnimation
{
public:
	std::wstring name{};

	// 애니메이션 사이의 간격 (1000당 1초)
	int delayTime = 100;
	std::vector<ExtractedSprite*> sprites;

	SpriteAnimation();
	~SpriteAnimation();
};

