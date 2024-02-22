#include "ShieldToDealer.h"
#include "Guardian.h"
#include "Dealer.h"

ShieldToDealer::ShieldToDealer(ManagerSet* _managers)
	: Object("ShieldFromSupporter", _managers, OBJECT_TYPE::EEFECT, { 0, 0 })
	, animation(nullptr)
	, dealer(nullptr)
	, isFull(false)
	, shieldElapseTime(0.f)
	, rangeSupporterShield(nullptr)
{

	isOnOff = false;
}

ShieldToDealer::~ShieldToDealer()
{

}

void ShieldToDealer::Start()
{
	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ -10,-30 });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void ShieldToDealer::Update(float _deltaTime)
{
	// maingamescene���� ������
	auto transform = CreateComponent<Transform>();
	Vector2 dealerPos = dealer->GetComponent<Transform>()->GetPosition();

	Vector2 offset = { -5,-30 };
	transform->SetPosition(dealerPos + offset);

	if (this->isOnOff == true)
	{
		this->shieldElapseTime += _deltaTime;
		if (this->shieldElapseTime >= 1.f)
		{
			this->isFull = true;
			if (this->shieldElapseTime >= this->SHIELD_TIME)
			{
				this->isOnOff = false;
				this->isFull = false;
				this->shieldElapseTime = 0.f;
			}
		}
	}

}

void ShieldToDealer::FinalUpdate(float _deltaTime)
{

}

void ShieldToDealer::Render(GraphicsEngine* _graphicsEngine)
{
	// �ð� �߰� ��
	// ä�����ɷ� ���α�
	if (isOnOff == true)
	{
		if (!this->isFull)
		{
			this->animation->SetSpriteRes(49, L"Animation\\ShieldEft.txt", "shieldeft",
				(int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		if (this->isFull == true)
		{
			this->animation->SetSpriteRes(51, L"Animation\\FullShieldEft.txt", "shieldeft",
				(int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
	}
	if (isOnOff == false)
	{
		this->animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr",
			(int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}

}

void ShieldToDealer::DebugRender(GraphicsEngine* _graphicsEngine)
{
	//// ������Ʈ �ǵ�, ���� �ʿ� ���� 0,0���� ������ �׷�����.
	//Vector2 position = this->GetComponent<Transform>()->GetPosition();
	//std::string stateString = "RangeSupporterSheild";
	//if (isOnOff)
	//{
	//	Vector2 tmp = SHEILD_RANGE + position;
	//	_graphicsEngine->DrawRectangle(position.x, position.y, tmp.x, tmp.y);
	//}
	//else
	//{

	//}
}

// TODO shield�� ���� ��ü�� �ߴµ� collision�� ��� �����ϴ��� ��
void ShieldToDealer::OnCollisionEnter(Object* _other)
{

}

void ShieldToDealer::OnCollisionStay(Object* _other)
{

}

void ShieldToDealer::OnCollisionExit(Object* _other)
{

}
