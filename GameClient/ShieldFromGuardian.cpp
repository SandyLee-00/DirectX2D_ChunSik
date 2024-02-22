#include "ShieldFromGuardian.h"
#include "Guardian.h"

ShieldFromGuardian::ShieldFromGuardian(ManagerSet* _managers)
	: Object("ShieldFromGuardian", _managers, OBJECT_TYPE::EEFECT, { 0, 0 })
	, guardian(nullptr)
	, shieldElapseTime(0.f)
	, isOnOff(false)
	, isFull(false)
	, animation(nullptr)
{
	isOnOff = false;
}

ShieldFromGuardian::~ShieldFromGuardian()
{

}

void ShieldFromGuardian::Start()
{
	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ -37.2f,-95.0f });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x,
		(int)GetComponent<Transform>()->GetPosition().y);
}

void ShieldFromGuardian::Update(float _deltaTime)
{
	auto transform = CreateComponent<Transform>();
	Vector2 guardianPos = guardian->GetComponent<Transform>()->GetPosition();

	Vector2 offset = { 5,25 };
	transform->SetPosition(guardianPos + offset);

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

void ShieldFromGuardian::FinalUpdate(float _deltaTime)
{

}

void ShieldFromGuardian::Render(GraphicsEngine* _graphicsEngine)
{
	if (isOnOff == true)
	{
		if (!this->isFull)
		{
			this->animation->SetSpriteRes(54, L"Animation\\GdnShieldEft.txt", "shieldeft",
				(int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		if (this->isFull == true)
		{
			this->animation->SetSpriteRes(55, L"Animation\\GdnFullShieldEft.txt", "shieldeft",
				(int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
	}
	if (isOnOff == false)
	{
		this->animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr",
			(int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}
}

void ShieldFromGuardian::DebugRender(GraphicsEngine* _graphicsEngine)
{

}

void ShieldFromGuardian::OnCollisionEnter(Object* _other)
{

}

void ShieldFromGuardian::OnCollisionStay(Object* _other)
{

}

void ShieldFromGuardian::OnCollisionExit(Object* _other)
{

}
