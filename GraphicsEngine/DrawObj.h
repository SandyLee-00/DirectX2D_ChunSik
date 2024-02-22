/// 그림을 그리는 오브젝트
///애니메이션모션 + 모션별 스프라이트 와 그냥 스프라이트의 정보를 가진다.
#pragma once
#include "D2DSprites.h"
#include "DrawMotions.h"
#include <vector>
#include <map>
class DrawObj 
{
public:
	std::vector<DrawMotions> Motions;
	std::map<std::string, D2DSprites> spriteMap;

	std::string name;

	// 오브젝트의 인덱스
	int index = 0;

	// 이 오브젝트의 모션 갯수
	int motionNum = 0;
};

