/// <summary>
/// ��������Ʈ ��ü�� �������� ������ Ŭ����
/// 7.27 �迹����
/// </summary>
#pragma once
#include <Windows.h>

class D2DSprites
{
public:
	//enum class SpriteType
	//{
	//	EBWTYPE, //���� �̹���
	//	EPICKPOS, // ��ġ�� ũ�⸸�� ������
	//	END
	//};

		//SpriteType spriteType;

	int sheetIndex;
	// ���������� ��ġ
	int oriX;
	int oriY;


	int index;

	int width;
	int height;

	int keycolor;

	int centorX;
	int centorY;
	int DelayFrame;

	//������� �� �ִ�. ������ �ϴ� �ҰŴ�
	RECT collision1;	// �浹����1 (e.g. �ǰ�)
	RECT collision2;	// �浹����2 (e.g. ����)
	int damage;			// ��ݷ�




	D2DSprites();
	///�Ⱦ��� �Ű������� ���� ���� : �׳� ���� SpriteType spriteType �̰� �Ⱦ��°Ű���
	D2DSprites( int _index, int _width, int _height, int _KeyColor,
		int _centerPosX, int _centerPosY, int _delayFrame, const RECT& _collision1,
		const RECT& _collision2, int _damage);
	~D2DSprites() {};
};

