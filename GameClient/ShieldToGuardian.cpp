#include "ShieldToGuardian.h"
#include "Guardian.h"

ShieldToGuardian::ShieldToGuardian(ManagerSet* _managers)
	: Object("ShieldToGuardian", _managers, OBJECT_TYPE::EEFECT, { 0,0 })
	, animation(nullptr)
	, guardian(nullptr)
	, isOnOff(false)
	, shieldElapseTime(0.f)
	, isFull(false)
	, rangeSupporterShield(nullptr)
{

}

ShieldToGuardian::~ShieldToGuardian()
{

}

void ShieldToGuardian::Start()
{
	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ -37.2f,-95.0f });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x,
		(int)GetComponent<Transform>()->GetPosition().y);
}

void ShieldToGuardian::Update(float _deltaTime)
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

void ShieldToGuardian::FinalUpdate(float _deltaTime)
{

}

void ShieldToGuardian::Render(GraphicsEngine* _graphicsEngine)
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

void ShieldToGuardian::DebugRender(GraphicsEngine* _graphicsEngine)
{

}

void ShieldToGuardian::OnCollisionEnter(Object* _other)
{

}

void ShieldToGuardian::OnCollisionStay(Object* _other)
{

}

void ShieldToGuardian::OnCollisionExit(Object* _other)
{

}
