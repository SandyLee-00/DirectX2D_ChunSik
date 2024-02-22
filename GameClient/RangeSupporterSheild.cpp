#include "RangeSupporterSheild.h"
#include "ShieldToDealer.h"

#include "Guardian.h"
#include "Dealer.h"
#include "Supporter.h"

// TODO: Range collider type ���ϱ� EFFECT / PLAYER
// RANGE / 
RangeSupporterSheild::RangeSupporterSheild(ManagerSet* _managers)
	: Object("RangeSupporterSheild", _managers, OBJECT_TYPE::ATTACHMENT, { 0, 0 })
	, shieldToDealer(nullptr)
	, shieldToGuardian(nullptr)
	, soundFlag(false)
{
	isOnOff = false;
	supporter = nullptr;
}

RangeSupporterSheild::~RangeSupporterSheild()
{

}

void RangeSupporterSheild::Start()
{
	// ������ ������ ����� / �������� �ǵ� ����Ʈ ���

	// �ǵ� ���� collider ����
	auto collider = CreateComponent<BoxCollider>();
	collider->SetOffset((SHEILD_RANGE / 3) * -1);
	collider->SetSize(SHEILD_RANGE);
	this->GetManagers()->GetCollisionManager()->AddCollider(collider);


	CreateComponent<Animation>();
	animation = GetComponent<Animation>();
	animation->SetOffset(Vector2{ -10,-30 });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void RangeSupporterSheild::Update(float _deltaTime)
{
	// OnOff �����Ϳ��� �ϱ�

	// ��ġ�� ������Ʈ
	auto transfrom = GetComponent<Transform>();
	auto parentPosition = supporter->GetComponent<Transform>()->GetPosition();

	// Offset��ŭ �θ𿡼� ������ ��ġ�� ����
	Vector2 offset = { 0, 0 };
	transfrom->SetPosition(parentPosition + offset);
}

void RangeSupporterSheild::FinalUpdate(float _deltaTime)
{

}

void RangeSupporterSheild::Render(GraphicsEngine* _graphicsEngine)
{
	// �����Ͱ� OnOff true�� �ٲٸ� �׸���

	if (isOnOff == true)
	{
		if (supporter->GetLookDirection() == DIRECTION::LEFT)
		{
			animation->SetSpriteRes(26, L"Animation\\Sup\\ShieldEftLeft.txt", "playersldeft", (int)GetComponent<Transform>()->GetPosition().x - 90, (int)GetComponent<Transform>()->GetPosition().y - 90);
		}
		if (supporter->GetLookDirection() == DIRECTION::RIGHT)
		{
			animation->SetSpriteRes(27, L"Animation\\Sup\\ShieldEftRight.txt", "playersldeft", (int)GetComponent<Transform>()->GetPosition().x - 90, (int)GetComponent<Transform>()->GetPosition().y - 90);
		}
	}

	if (isOnOff == false)
	{
		animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}
}

void RangeSupporterSheild::DebugRender(GraphicsEngine* _graphicsEngine)
{
	// �ǵ� ���� �׸���
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "RangeSupporterSheild";

	if (isOnOff == true)
	{
		stateString += "On";
		Vector2 tmp = SHEILD_RANGE + position;
		//_graphicsEngine->DrawRectangle(position.x, position.y, tmp.x, tmp.y);
	}
	else if (isOnOff == false)
	{
		stateString += "Off";
	}

	_graphicsEngine->DrawString((int)position.x, (int)position.y - 50, stateString);

}

void RangeSupporterSheild::OnCollisionEnter(Object* _other)
{

}

void RangeSupporterSheild::OnCollisionStay(Object* _other)
{
	// 
	if (isOnOff == false)
	{
		this->soundFlag = false;
		return;
	}

	// 1. 
	if (_other->GetName() == "Guardian")
	{
		// ����𿡰� �ǵ� ����Ʈ ���
		auto guardian = dynamic_cast<Guardian*>(_other);
		guardian->SetSupShield(true);
		if (!this->soundFlag)
		{
			SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::SHILDING);
			this->soundFlag = true;
		}
	}
	else if (_other->GetName() == "Dealer")
	{
		// �������� �ǵ� ����Ʈ ���
		auto dealer = dynamic_cast<Dealer*>(_other);
		dealer->SetSupShield(true);
		if (!this->soundFlag)
		{
			SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::SHILDING);
			this->soundFlag = true;
		}
	}
}

void RangeSupporterSheild::OnCollisionExit(Object* _other)
{

}
