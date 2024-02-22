#include "ResourceManager.h"

ID2D1Bitmap* ResourceManager::LoadHBITMAP(int _scene, const char* _path)
{
	char* dest;
	dest = pathMgr.GetResourcePath(_scene);
	strcat_s(dest, MAX_PATH, "Bitmap\\");


	strcat_s(dest, MAX_PATH, _path);
	char dest2[MAX_PATH];
	memset(dest2, 0, MAX_PATH);
	for (int i = 0; i < MAX_PATH; i++)
	{
		dest2[i] = dest[i];
	}

	return (ID2D1Bitmap*)LoadImageA(NULL, dest2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void ResourceManager::LoadAllResources()
{
	///���⿡ ������ �߰��ϴ°Ŵ�
	LoadExampleResources();
}

void ResourceManager::LoadExampleResources()
{
	example.exampleBitmap = LoadHBITMAP(pathMgr.EX, "image.bmp");
}

void ResourceManager::Init()
{
	pathMgr.Init();
	LoadAllResources();
}

DrawObj* ResourceManager::MakeGameObject_Old(int _motion, int _sprite,std::string _name)
{
	DrawObj* _newObject = new DrawObj();
	//_newObject->Name = name;
	//_newObject->Index = m_DrObjects.size();	// �ε����� 0����

	ReadHeaderfile_fromOldSLEngine(_motion, _sprite,_newObject);

	//m_DrObjects.push_back(_newObject);

	return _newObject;
}

bool ResourceManager::MakeSpriteData_Temp(DrawObj* _object, int _spriteSheetIndex)
{
	int _spriteWidthTemp[4] = { 125, 125, 125, 125, };
	int _spriteHeightTemp[4] = { 120, 120, 120, 120 };

	int _oriPosX = 0;
	int _oriPosY = 0;

	for (int j = 0; j < _object->motionNum; j++)
	{
		for (int i = 0; i < _object->Motions[j]->SpriteNum; i++)
		{
			// D2DSprite (PickPos)���� �ִ� ����
			_object->Motions[j]->motionSprites[i]->sheetIndex = 0;
			_object->Motions[j]->motionSprites[i]->oriX = _oriPosX;	// ���� ��������Ʈ ��Ʈ�κ����� ��ġ�̸�, �̹����� ���� ������ �־�� �Ѵ�.
			_object->Motions[j]->motionSprites[i]->oriY = _oriPosY;

			// DRSprite�� �ִ� ����
			//�ߴپߴ�
			//_object->Motions[j]->motionSprites[i]->spriteType = D2DSprite::SpriteType::ePickPos;
			_object->Motions[j]->motionSprites[i]->index = i;
			_object->Motions[j]->motionSprites[i]->width = _spriteWidthTemp[j];	// Bitmap�� �������� ������������, �̹����� ���� ������ �־�� �Ѵ�.
			_object->Motions[j]->motionSprites[i]->height = _spriteHeightTemp[j];
			_object->Motions[j]->motionSprites[i]->keycolor = RGB(255, 0, 255);	// Direct2D������ ���� �ʴ´�.

			_oriPosX += _spriteWidthTemp[j];
		}

		// �� ó�� �ٷ� �ǵ��ư��Ƿ�
		_oriPosX = 0;
		_oriPosY += _spriteHeightTemp[j];
	}
	return true;
}

bool ResourceManager::ReadHeaderfile_fromOldSLEngine(int _motion, int _sprite,DrawObj* object)
{
	if (object == nullptr)
	{
		return false;
	}

	object->motionNum = _motion;

	// ��� ������ŭ ���鼭, �� ��Ǵ� ��������Ʈ�� ������ ��´�.
	for (int i = 0; i < object->motionNum; i++)
	{
		// ����� �����Ѵ�.
		DrawMotions* _newMotion = new DrawMotions();
		_newMotion->Index = i;
		_newMotion->SpriteNum = _sprite;

		object->Motions.push_back(_newMotion);
	}

	for (int i = 0; i < object->motionNum; i++)
	{
		for (int j = 0; j < object->Motions[i]->SpriteNum; j++)
		{
			// �ϴ� ��� 0���� ������ ��� ����.
			D2DSprites* _newD2DSprite = new D2DSprites();
			object->Motions[i]->motionSprites.push_back(_newD2DSprite);
		}
	}

	return true;
}

//DrawObj* ResourceManager::GetResouce(int _posX, int _posY, int _width, int _height)
//{
//	//D2DSprites* _newD2DSprite = new D2DSprites();
//	//DrawObj* object = new DrawObj();
//	////object->sprites.pushback(_newD2DSprite);
//	//object->spriteMap.insert(std::make_pair("exmaple", _newD2DSprite));
//
//	//object->spriteMap["exmaple"]->sheetIndex = 0;
//	//object->spriteMap["exmaple"]->oriX = _posX;
//	//object->spriteMap["exmaple"]->oriY = _posY;
//	//object->spriteMap["exmaple"]->index = 0;
//	//object->spriteMap["exmaple"]->width = _width;
//	//object->spriteMap["exmaple"]->height = _height;
//	//return object;
//}
