#include "TextFrozenCount.h"
#include "Monster.h"

TextFrozenCount::TextFrozenCount(ManagerSet* _managers)
	: Object("TextFrozenCount", _managers, OBJECT_TYPE::UI, { 0, 0 })
{
	isWorking = true;
	HOLDMonsterCount = 0;
}

TextFrozenCount::~TextFrozenCount()
{

}

void TextFrozenCount::Start()
{
	HOLDMonsterCount = 0;
}

void TextFrozenCount::Update(float _deltaTime)
{

}

void TextFrozenCount::Render(GraphicsEngine* _graphicsEngine)
{
	_graphicsEngine->DrawSprite("frozbox", 66, 24, 10, 252, 95);
	_graphicsEngine->DrawSprite("frozeCount", 24, 56, 20, 67, 67);
	std::string frozenCountString = "X " + std::to_string(HOLDMonsterCount);
	
	_graphicsEngine->ChangeFontSize(46.f);
	_graphicsEngine->ColorSet(D2D1::ColorF::White);
	_graphicsEngine->DrawString(150, 30, frozenCountString);
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(12.f);

	//TO DO : 안그려지는 버그 수정
	//switch (HOLDMonsterCount)
	//{
	//case 0:
	//	_graphicsEngine->DrawSprite("pskillbar", 43, 701, 1010, 102, 18);
	//	break;
	//case 1:
	//	_graphicsEngine->DrawSprite("pskillbar1", 44, 701, 1010, 102, 18);
	//	break;
	//case 2:
	//	_graphicsEngine->DrawSprite("pskillbar2", 45, 701, 1010, 102, 18);
	//	break;
	//case 3:
	//	_graphicsEngine->DrawSprite("pskillbar3", 46, 701, 1010, 102, 18);
	//	break;
	//case 4:
	//	_graphicsEngine->DrawSprite("pskillbar4", 47, 701, 1010, 102, 18);
	//	break;
	//case 5:
	//	_graphicsEngine->DrawSprite("pskillbar5", 48, 701, 1010, 102, 18);
	//	break;
	//default:
	//	break;
	//}

}

void TextFrozenCount::PlusCount()
{
	this->HOLDMonsterCount++;
}

void TextFrozenCount::MinusCount()
{
	this->HOLDMonsterCount--;

}

