/// �׸��� �׸��� ������Ʈ
///�ִϸ��̼Ǹ�� + ��Ǻ� ��������Ʈ �� �׳� ��������Ʈ�� ������ ������.
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

	// ������Ʈ�� �ε���
	int index = 0;

	// �� ������Ʈ�� ��� ����
	int motionNum = 0;
};

