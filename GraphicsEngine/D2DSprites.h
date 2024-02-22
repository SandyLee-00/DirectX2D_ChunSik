/// <summary>
/// 스프라이트 자체의 정보만을 가지는 클래스
/// 7.27 김예리나
/// </summary>
#pragma once
#include <Windows.h>

class D2DSprites
{
public:
	//enum class SpriteType
	//{
	//	EBWTYPE, //실제 이미지
	//	EPICKPOS, // 위치와 크기만을 가진다
	//	END
	//};

		//SpriteType spriteType;

	int sheetIndex;
	// 원본에서의 위치
	int oriX;
	int oriY;


	int index;

	int width;
	int height;

	int keycolor;

	int centorX;
	int centorY;
	int DelayFrame;

	//쓸모없을 수 있다. 하지만 일단 할거다
	RECT collision1;	// 충돌영역1 (e.g. 피격)
	RECT collision2;	// 충돌영역2 (e.g. 공격)
	int damage;			// 충격량




	D2DSprites();
	///안쓰는 매개변수도 넣은 이유 : 그냥 냅둬 SpriteType spriteType 이건 안쓰는거같다
	D2DSprites( int _index, int _width, int _height, int _KeyColor,
		int _centerPosX, int _centerPosY, int _delayFrame, const RECT& _collision1,
		const RECT& _collision2, int _damage);
	~D2DSprites() {};
};

