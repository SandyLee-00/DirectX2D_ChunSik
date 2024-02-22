#include "BarDealerZ.h"
#include "Monster.h"

BarDealerZ::BarDealerZ(ManagerSet* _managers)
	: Object("BarDealerZ", _managers, OBJECT_TYPE::UI, { 0, 0 }), Z(5)
{
	parent = nullptr;
}

BarDealerZ::~BarDealerZ()
{

}

void BarDealerZ::Start()
{
	//SetMaxZ(MaxZ);
	Z = 5;
}

void BarDealerZ::Update(float _deltaTime)
{
}

void BarDealerZ::FinalUpdate(float _deltaTime)
{

}

void BarDealerZ::Render(GraphicsEngine* _graphicsEngine)
{
	if (Z <= 0)
	{
		_graphicsEngine->DrawSprite("dskillbar", 43, 939, 1010 + 34, 102, 18);
	}
	else if (Z == 1)
	{
		_graphicsEngine->DrawSprite("dskillbar1", 44, 939, 1010 + 34, 102, 18);
	}
	else if (Z == 2)
	{
		_graphicsEngine->DrawSprite("dskillbar2", 45, 939, 1010 + 34, 102, 18);
	}
	else if (Z == 3)
	{
		_graphicsEngine->DrawSprite("dskillbar3", 46, 939, 1010 + 34, 102, 18);
	}
	else if (Z == 4)
	{
		_graphicsEngine->DrawSprite("dskillbar4", 47, 939, 1010 + 34, 102, 18);
	}
	else if (Z >= 5)
	{
		_graphicsEngine->DrawSprite("dskillbar5", 48, 939, 1010 + 34, 102, 18);
	}
}

void BarDealerZ::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = parent->GetComponent<Transform>()->GetPosition();

	// 펜 크기 키우기
	_graphicsEngine->ChangeFontSize(30.f);

	std::string stateString = "Z : ";

	// HP에 따라 이미지 리소스 변경
	stateString += std::to_string(Z);

	_graphicsEngine->DrawString((int)position.x, (int)position.y - 40, stateString);

	// 펜 크기 원래대로
	_graphicsEngine->ChangeFontSize(12.f);
}

void BarDealerZ::SubZ()
{
	if (this->Z > 0) 
	{
		this->Z--;
	}
	else
	{
		return;
	}
}
