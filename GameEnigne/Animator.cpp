#include "Animator.h"
#include "ManagerSet.h"
#include "Object.h"
// �� �߰��ؾ� �Ǵ� ���̺귯��
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

	//��������� txt ������ �����´�.
	//std::wstring path = pm->GetResourcePath(_fileImagePath);
	std::wstring path2 = pm->GetResourcePath(_fileParcingPath);

	D2DSprites newD2DSprite = D2DSprites();
	DrawObj* _graphicsObj = new  DrawObj();

	//�Ľ��� ���ϰ� ������Ų��..��������� �����޾Ƽ�
	std::wifstream ifs(path2);

	if (ifs.is_open())
	{
		// �� ����� ��������Ʈ �� n
		spriteCount = 0;
		ifs >> spriteCount;
		//std::wcout << spriteCount << std::endl;

		Left = new float[spriteCount] {0, };
		Top = new float[spriteCount] {0, };
		Right = new float[spriteCount] {0, };
		Bottom = new float[spriteCount] {0, };
		PivotX = new float[spriteCount] {0, };
		PivotY = new float[spriteCount] {0, };

		// ����� �̸�
		std::wstring name{};
		ifs >> name;
		//std::wcout << name << std::endl;

		// ������
		frame = 0;
		ifs >> frame;
		frame /= 1000;
		//std::wcout << frame << std::endl;

		/// ó���� \n �����鼭 ù��° ���� ����� �� ������
		std::wstring line;
		std::getline(ifs, line);

		//n���� ��ŭ �������̴�. �ݺ��� �Ȱ��� ���� 
		for (int i = 0; i < spriteCount; i++)
		{
			int count = 0;
			while (std::getline(ifs, line))
			{
				assert(count < spriteCount && "spritCount and count is not inavlied\n");
				std::wistringstream iss(line);


				std::getline(iss, spriteName, L',');
				//std::wcout << spriteName << L",";

				// ��
				std::wstring left;
				std::getline(iss, left, L',');
				Left[count] = std::stof(left);
				//std::wcout << Left << L",";

				// ��
				std::wstring top;
				std::getline(iss, top, L',');
				Top[count] = std::stof(top);
				//std::wcout << Top << L",";

				// ��
				std::wstring right;
				std::getline(iss, right, L',');
				Right[count] = std::stof(right);
				//std::wcout << Right << L",";

				// ��
				std::wstring bottom;
				std::getline(iss, bottom, L',');
				Bottom[count] = std::stof(bottom);
				//std::wcout << Bottom << L",";

				// x�� �ǹ�
				std::wstring pivotX;
				std::getline(iss, pivotX, L',');
				PivotX[count] = std::stof(pivotX);
				//std::wcout << PivotX << L",";

				// y�� �ǹ�
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

	// ��� ������ŭ ���鼭, �� ��Ǵ� ��������Ʈ�� ������ ��´�.
	for (int i = 0; i < _graphicsObj->motionNum; i++)
	{
		// ����� �����Ѵ�.
		DrawMotions _newMotion = DrawMotions();
		_newMotion.Index = i;
		_newMotion.SpriteNum = spriteCount;

		_graphicsObj->Motions.push_back(_newMotion);
	}

	for (int j = 0; j < _graphicsObj->Motions[0].SpriteNum; j++)
	{
		// �ϴ� ��� 0���� ������ ��� ����.
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

			// D2DSprite (PickPos)���� �ִ� ����
			_graphicsObj->Motions[j].motionSprites[i].sheetIndex = 0;
			_graphicsObj->Motions[j].motionSprites[i].oriX = _oriPosX;	// ���� ��������Ʈ ��Ʈ�κ����� ��ġ�̸�, �̹����� ���� ������ �־�� �Ѵ�.
			_graphicsObj->Motions[j].motionSprites[i].oriY = _oriPosY;

			// DRSprite�� �ִ� ����
			//�ߴپߴ�
			//_object->Motions[j]->motionSprites[i]->spriteType = D2DSprite::SpriteType::ePickPos;
			_graphicsObj->Motions[j].motionSprites[i].index = i;
			_graphicsObj->Motions[j].motionSprites[i].width = spriteWidthTemp[j];	// Bitmap�� �������� ������������, �̹����� ���� ������ �־�� �Ѵ�.
			_graphicsObj->Motions[j].motionSprites[i].height = spriteHeightTemp[j];
			_graphicsObj->Motions[j].motionSprites[i].keycolor = RGB(255, 0, 255);	// Direct2D������ ���� �ʴ´�.
		}

		// �� ó�� �ٷ� �ǵ��ư��Ƿ�
		//������ ����� �ǹ̰� ���� ��..�ƴҼ���
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
