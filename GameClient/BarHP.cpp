#include "BarHP.h"
#include "ClientHeaders.h"
#include "ClientDefines.h"

#include "Guardian.h"
#include "Dealer.h"
#include "Supporter.h"

BarHP::BarHP(ManagerSet* _managers)
	: Object("BarHP", _managers, OBJECT_TYPE::UI, { 0, 0 })
{
	parent = nullptr;
}

BarHP::~BarHP()
{

}

void BarHP::Start()
{
	// MaxHP�� ���� ���ҽ� ����
	if (MaxHP == 7)
	{
		// ����� HP�� ���ҽ�
	}


}

void BarHP::Update(float _deltaTime)
{
	if (parent->GetName() == "Guardian")
	{
		Guardian* guardian = dynamic_cast<Guardian*>(parent);
		HP = guardian->GetHP();
	}
	else if (parent->GetName() == "Dealer")
	{
		Dealer* dealer = dynamic_cast<Dealer*>(parent);
		HP = dealer->GetHP();
	}
	else if (parent->GetName() == "Supporter")
	{
		Supporter* supporter = dynamic_cast<Supporter*>(parent);
		HP = supporter->GetHP();
	}
	
}

void BarHP::FinalUpdate(float _deltaTime)
{

}

void BarHP::Render(GraphicsEngine* _graphicsEngine)
{
	// HP�� ���� �̹��� ���ҽ� ����
	// @@@ �׷��� �� parent ���� ��ġ �����ؼ� �׷��ֱ� @@@
	Vector2 position = parent->GetComponent<Transform>()->GetPosition();
	switch (HP)
	{
	case 5:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP", 37, 1177, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Dealer")
		{
			Dealer* dealer = dynamic_cast<Dealer*>(parent);
			_graphicsEngine->DrawSprite("dHP", 37, 939, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Supporter")
	 	{
			Supporter* supporter = dynamic_cast<Supporter*>(parent);
			_graphicsEngine->DrawSprite("sHP", 37, 701, 980 + 34, 102, 18);
		}
		break;
	case 4:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP1", 38, 1177, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Dealer")
		{
			Dealer* dealer = dynamic_cast<Dealer*>(parent);
			_graphicsEngine->DrawSprite("dHP", 38, 939, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Supporter")
		{
			Supporter* supporter = dynamic_cast<Supporter*>(parent);
			_graphicsEngine->DrawSprite("sHP", 38, 701, 980 + 34, 102, 18);
		}
		break;
	case 3:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP", 39, 1177, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Dealer")
		{
			Dealer* dealer = dynamic_cast<Dealer*>(parent);
			_graphicsEngine->DrawSprite("dHP", 39, 939, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Supporter")
		{
			Supporter* supporter = dynamic_cast<Supporter*>(parent);
			_graphicsEngine->DrawSprite("sHP", 39, 701, 980 + 34, 102, 18);
		}
		break;
	case 2:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP", 40, 1177, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Dealer")
		{
			Dealer* dealer = dynamic_cast<Dealer*>(parent);
			_graphicsEngine->DrawSprite("dHP", 40, 939, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Supporter")
		{
			Supporter* supporter = dynamic_cast<Supporter*>(parent);
			_graphicsEngine->DrawSprite("sHP", 40, 701, 980 + 34, 102, 18);
		}
		break;
	case 1:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP", 41, 1177, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Dealer")
		{
			Dealer* dealer = dynamic_cast<Dealer*>(parent);
			_graphicsEngine->DrawSprite("dHP", 41, 939, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Supporter")
		{
			Supporter* supporter = dynamic_cast<Supporter*>(parent);
			_graphicsEngine->DrawSprite("sHP", 41, 701, 980 + 34, 102, 18);
		}
		break;
	case 0:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP", 42, 1177, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Dealer")
		{
			Dealer* dealer = dynamic_cast<Dealer*>(parent);
			_graphicsEngine->DrawSprite("dHP", 42, 939, 980 + 34, 102, 18);
		}
		else if (parent->GetName() == "Supporter")
		{
			Supporter* supporter = dynamic_cast<Supporter*>(parent);
			_graphicsEngine->DrawSprite("sHP", 42, 701, 980 + 34, 102, 18);
		}
		break;
	default:
		if (parent->GetName() == "Guardian")
		{
			Guardian* guardian = dynamic_cast<Guardian*>(parent);
			_graphicsEngine->DrawSprite("gHP", 42, 1177, 980 + 34, 102, 18);
		}
// 		else if (parent->GetName() == "Dealer")
// 		{
// 			Dealer* dealer = dynamic_cast<Dealer*>(parent);
// 			_graphicsEngine->DrawSprite("dHP", 42, 939, 980 + 34, 102, 18);
// 		}
// 		else if (parent->GetName() == "Supporter")
// 		{
// 			Supporter* supporter = dynamic_cast<Supporter*>(parent);
// 			_graphicsEngine->DrawSprite("sHP", 42, 701, 980 + 34, 102, 18);
// 		}
		break;
	}

}

void BarHP::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = parent->GetComponent<Transform>()->GetPosition();
	std::string stateString = "BAR";

	// HP�� ���� �̹��� ���ҽ� ����
	stateString += "HP: " + std::to_string(HP);

	_graphicsEngine->DrawString((int)position.x, (int)position.y - 20, stateString);
}
