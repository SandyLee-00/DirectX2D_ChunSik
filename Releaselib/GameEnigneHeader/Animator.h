///�ִϸ��̼� ������ ������.
///���⼭ ������ ������ �ִϸ��̼��� ������ ,, �߽�..���..
/// by. �迹����
#pragma once
#include "headers.h"
#include "DrawObj.h"
#include "ManagerSet.h"

class Animator
{
	ManagerSet* managers = nullptr;
	FILE* textFile = nullptr;
	int spriteCount = 0;

	// ������
	float frame = 0;

	// ��������Ʈ �̸�
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

	//�ִϸ��̼� ������ �����ϴ�.
	DrawObj* GetAnimationInfo(ManagerSet* _manger, std::wstring _fileParcingPath, std::string _name, int spriteSheetIndex);
	float GetFrame();
};

