#include "Animator.h"
#include "ManagerSet.h"
#include "Object.h"
// 꼭 추가해야 되는 라이브러리
#include <fstream>
#include <sstream>

Animator::Animator()
	:Left(nullptr), Right(nullptr), Top(nullptr), Bottom(nullptr)
{

}

Animator::~Animator()
{
}

DrawObj* Animator::GetAnimationInfo(ManagerSet* _manger, std::wstring _fileParcingPath, std::string _name, int spriteSheetIndex)
{
	ResourceManager* rm = _manger->GetResourceManager();
	PathManager* pm = _manger->GetPathManager();
	//rm->LoadImage(_name, pm->GetResourcePath(_fileImagePath));

	//정우오빠의 txt 파일을 가져온다.
	//std::wstring path = pm->GetResourcePath(_fileImagePath);
	std::wstring path2 = pm->GetResourcePath(_fileParcingPath);

	D2DSprites newD2DSprite = D2DSprites();
	DrawObj* _graphicsObj = new  DrawObj();

	//파싱한 파일과 연동시킨다..정우오빠의 것을받아서
	std::wifstream ifs(path2);

	if (ifs.is_open())
	{
		// 각 모션의 스프라이트 수 n
		spriteCount = 0;
		ifs >> spriteCount;
		//std::wcout << spriteCount << std::endl;

		Left = new float[spriteCount] {0, };
		Top = new float[spriteCount] {0, };
		Right = new float[spriteCount] {0, };
		Bottom = new float[spriteCount] {0, };
		PivotX = new float[spriteCount] {0, };
		PivotY = new float[spriteCount] {0, };

		// 모션의 이름
		std::wstring name{};
		ifs >> name;
		//std::wcout << name << std::endl;

		// 프레임
		frame = 0;
		ifs >> frame;
		frame /= 1000;
		//std::wcout << frame << std::endl;

		/// 처음에 \n 만나면서 첫번째 줄이 제대로 안 잡힌다
		std::wstring line;
		std::getline(ifs, line);

		//n개의 만큼 있을것이다. 반복문 똑같이 돌려 
		for (int i = 0; i < spriteCount; i++)
		{
			int count = 0;
			while (std::getline(ifs, line))
			{
				assert(count < spriteCount && "spritCount and count is not inavlied\n");
				std::wistringstream iss(line);


				std::getline(iss, spriteName, L',');
				//std::wcout << spriteName << L",";

				// 좌
				std::wstring left;
				std::getline(iss, left, L',');
				Left[count] = std::stof(left);
				//std::wcout << Left << L",";

				// 상
				std::wstring top;
				std::getline(iss, top, L',');
				Top[count] = std::stof(top);
				//std::wcout << Top << L",";

				// 우
				std::wstring right;
				std::getline(iss, right, L',');
				Right[count] = std::stof(right);
				//std::wcout << Right << L",";

				// 하
				std::wstring bottom;
				std::getline(iss, bottom, L',');
				Bottom[count] = std::stof(bottom);
				//std::wcout << Bottom << L",";

				// x축 피벗
				std::wstring pivotX;
				std::getline(iss, pivotX, L',');
				PivotX[count] = std::stof(pivotX);
				//std::wcout << PivotX << L",";

				// y축 피벗
				std::wstring pivotY;
				std::getline(iss, pivotY, L',');
				PivotY[count] = std::stof(pivotY);
				//std::wcout << PivotY << L",";
				//std::wcout << std::endl;
				count++;
			}
		}
	}

	_graphicsObj->motionNum = 1;

	// 모션 갯수만큼 돌면서, 각 모션당 스프라이트의 갯수를 얻는다.
	for (int i = 0; i < _graphicsObj->motionNum; i++)
	{
		// 모션을 생성한다.
		DrawMotions _newMotion = DrawMotions();
		_newMotion.Index = i;
		_newMotion.SpriteNum = spriteCount;

		_graphicsObj->Motions.push_back(_newMotion);
	}

	for (int j = 0; j < _graphicsObj->Motions[0].SpriteNum; j++)
	{
		// 일단 모두 0으로 생성만 모두 하자.
		D2DSprites _newD2DSprite = D2DSprites();
		_graphicsObj->Motions[0].motionSprites.push_back(_newD2DSprite);
	}

	int _oriPosX = 0;
	int _oriPosY = 0;

	int* spriteWidthTemp = new int[spriteCount];
	int* spriteHeightTemp = new int[spriteCount];

	for (int i = 0; i < spriteCount; i++)
	{
		int width = (int)(Right[i] - Left[i]);
		spriteWidthTemp[i] = width;
	}

	for (int i = 0; i < spriteCount; i++)
	{
		int height = (int)(Bottom[i] - Top[i]);
		spriteHeightTemp[i] = height;
	}

	for (int j = 0; j < _graphicsObj->motionNum; j++)
	{
		for (int i = 0; i < _graphicsObj->Motions[j].SpriteNum; i++)
		{
			assert(i < spriteCount && "Something worng at Animaiton Load\n");

			_oriPosX = (int)Left[i];

			// D2DSprite (PickPos)에만 있는 내용
			_graphicsObj->Motions[j].motionSprites[i].sheetIndex = 0;
			_graphicsObj->Motions[j].motionSprites[i].oriX = _oriPosX;	// 원본 스프라이트 시트로부터의 위치이며, 이번에는 각자 가지고 있어야 한다.
			_graphicsObj->Motions[j].motionSprites[i].oriY = _oriPosY;

			// DRSprite에 있는 내용
			//야다야다
			//_object->Motions[j]->motionSprites[i]->spriteType = D2DSprite::SpriteType::ePickPos;
			_graphicsObj->Motions[j].motionSprites[i].index = i;
			_graphicsObj->Motions[j].motionSprites[i].width = spriteWidthTemp[j];	// Bitmap을 기준으로 만들어줬었으나, 이번에는 각자 가지고 있어야 한다.
			_graphicsObj->Motions[j].motionSprites[i].height = spriteHeightTemp[j];
			_graphicsObj->Motions[j].motionSprites[i].keycolor = RGB(255, 0, 255);	// Direct2D에서는 쓰지 않는다.
		}

		// 맨 처음 줄로 되돌아가므로
		//어차피 여기는 의미가 없다 ㅎ..아닐수도
		_oriPosX = 0;
		_oriPosY += spriteHeightTemp[j];
	}

	delete[] spriteWidthTemp;
	delete[] spriteHeightTemp;

	delete[] Left;
	delete[] Top;
	delete[] Right;
	delete[] Bottom;
	delete[] PivotX;
	delete[] PivotY;

	return _graphicsObj;
}

float Animator::GetFrame()
{
	return frame;
}
