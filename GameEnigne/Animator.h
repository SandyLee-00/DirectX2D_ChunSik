///애니메이션 정보를 가진다.
///여기서 정보를 가져서 애니메이션의 꼭짓점 ,, 중심..등등..
/// by. 김예리나
#pragma once
#include "headers.h"
#include "DrawObj.h"
#include "ManagerSet.h"

class Animator
{
	ManagerSet* managers = nullptr;
	FILE* textFile = nullptr;
	int spriteCount = 0;

	// 프레임
	float frame = 0;

	// 스프라이트 이름
	std::wstring spriteName;

	float* Left;
	float* Top;
	float* Right;
	float* Bottom;
	float* PivotX = nullptr;
	float* PivotY = nullptr;
public:
	Animator();
	virtual ~Animator();

	//애니메이션 정보를 가집니다.
	DrawObj* GetAnimationInfo(ManagerSet* _manger, std::wstring _fileParcingPath, std::string _name, int spriteSheetIndex);
	float GetFrame();
};

