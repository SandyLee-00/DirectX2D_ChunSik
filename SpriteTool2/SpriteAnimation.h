#pragma once

#include <string>
#include <vector>

class ExtractedSprite;

class SpriteAnimation
{
public:
	std::wstring name{};

	// �ִϸ��̼� ������ ���� (1000�� 1��)
	int delayTime = 100;
	std::vector<ExtractedSprite*> sprites;

	SpriteAnimation();
	~SpriteAnimation();
};

