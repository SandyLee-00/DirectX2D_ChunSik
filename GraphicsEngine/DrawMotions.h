///�ִϸ��̼� ���Ŭ����
///��Ǻ� ���ö���Ʈ�� ���ͷ� ������.
#pragma once
#include <iostream>
#include <vector>
#include "D2DSprites.h"
class DrawMotions
{
public:
	// ����� �̸�
	std::string Name;

	// ����� �ε���
	int Index = 0;

	// �� ����� ��������Ʈ ����
	int SpriteNum = 0;

	// �� ��ǿ� ����ִ� ��������Ʈ��
	std::vector<D2DSprites> motionSprites;

	//void AddSprite(D2DSprite* sprite);
};

