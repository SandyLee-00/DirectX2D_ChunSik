///애니메이션 모션클래스
///모션별 스플라이트를 벡터로 가진다.
#pragma once
#include <iostream>
#include <vector>
#include "D2DSprites.h"
class DrawMotions
{
public:
	// 모션의 이름
	std::string Name;

	// 모션의 인덱스
	int Index = 0;

	// 이 모션의 스프라이트 갯수
	int SpriteNum = 0;

	// 이 모션에 들어있는 스프라이트들
	std::vector<D2DSprites> motionSprites;

	//void AddSprite(D2DSprite* sprite);
};

