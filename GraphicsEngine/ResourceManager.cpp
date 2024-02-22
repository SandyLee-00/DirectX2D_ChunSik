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
	///여기에 더더더 추가하는거다
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
	//_newObject->Index = m_DrObjects.size();	// 인덱스는 0부터

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
			// D2DSprite (PickPos)에만 있는 내용
			_object->Motions[j]->motionSprites[i]->sheetIndex = 0;
			_object->Motions[j]->motionSprites[i]->oriX = _oriPosX;	// 원본 스프라이트 시트로부터의 위치이며, 이번에는 각자 가지고 있어야 한다.
			_object->Motions[j]->motionSprites[i]->oriY = _oriPosY;

			// DRSprite에 있는 내용
			//야다야다
			//_object->Motions[j]->motionSprites[i]->spriteType = D2DSprite::SpriteType::ePickPos;
			_object->Motions[j]->motionSprites[i]->index = i;
			_object->Motions[j]->motionSprites[i]->width = _spriteWidthTemp[j];	// Bitmap을 기준으로 만들어줬었으나, 이번에는 각자 가지고 있어야 한다.
			_object->Motions[j]->motionSprites[i]->height = _spriteHeightTemp[j];
			_object->Motions[j]->motionSprites[i]->keycolor = RGB(255, 0, 255);	// Direct2D에서는 쓰지 않는다.

			_oriPosX += _spriteWidthTemp[j];
		}

		// 맨 처음 줄로 되돌아가므로
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

	// 모션 갯수만큼 돌면서, 각 모션당 스프라이트의 갯수를 얻는다.
	for (int i = 0; i < object->motionNum; i++)
	{
		// 모션을 생성한다.
		DrawMotions* _newMotion = new DrawMotions();
		_newMotion->Index = i;
		_newMotion->SpriteNum = _sprite;

		object->Motions.push_back(_newMotion);
	}

	for (int i = 0; i < object->motionNum; i++)
	{
		for (int j = 0; j < object->Motions[i]->SpriteNum; j++)
		{
			// 일단 모두 0으로 생성만 모두 하자.
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
