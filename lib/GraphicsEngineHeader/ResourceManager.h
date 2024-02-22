///리소스를 만들거다.
///7.30
#pragma once
#include "Resources.h"
#include "PathManager.h"
#include "DrawObj.h"
#include "DrawMotions.h"
#include <string>
#include <iostream>

class ResourceManager
{
	ID2D1Bitmap* LoadHBITMAP(int _scene, const char* _path);
	void LoadAllResources();
	void LoadExampleResources();
public:
	ExampleBitmap example;
	PathManager pathMgr;

	void Init();
	DrawObj* MakeGameObject_Old(int _motion,  int _sprite, std::string _name);
	bool MakeSpriteData_Temp(DrawObj* _object, int _spriteSheetIndex);
	bool ReadHeaderfile_fromOldSLEngine(int _motion, int _sprite,  DrawObj* object);
};

