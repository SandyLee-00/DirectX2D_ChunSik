#include "GuardianAttackEffect.h"
#include "Monster.h"

GuardianAttackEffect::GuardianAttackEffect(ManagerSet* _managers)
	: Object("GuardianAttackEffect", _managers, OBJECT_TYPE::ATTACHMENT, { 0,0 })
	, animation(nullptr)
	, isOnOff(false)
	, elapsedTime(0.f)
	, monster(nullptr)
	, soundFlag(false)
{

}

GuardianAttackEffect::~GuardianAttackEffect()
{

}

void GuardianAttackEffect::Start()
{
	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ 0,-50 });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void GuardianAttackEffect::Update(float _deltaTime)
{
	auto transform = CreateComponent<Transform>();
	Vector2 monPos = monster->GetComponent<Transform>()->GetPosition();
	Vector2 offset = { 0,0 };
	transform->SetPosition(monPos + offset);

	if (isOnOff)
	{
		elapsedTime += _deltaTime;
		if (elapsedTime >= 0.4f)
		{
			isOnOff = false;
			elapsedTime = 0.f;
		}
	}
}

void GuardianAttackEffect::FinalUpdate(float _deltaTime)
{

}

void GuardianAttackEffect::Render(GraphicsEngine* _graphicsEngine)
{
	if (isOnOff)
	{
		if (!this->soundFlag)
		{
			SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
			this->soundFlag = true;
		}
		animation->SetSpriteRes(79, L"Animation\\GdnAtkEft.txt", "GdnAtkEft", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}
	if (!isOnOff)
	{
		animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		this->soundFlag = false;
	}
}

void GuardianAttackEffect::DebugRender(GraphicsEngine* _graphicsEngine)
{

}

void GuardianAttackEffect::OnCollisionEnter(Object* _other)
{

}

void GuardianAttackEffect::OnCollisionStay(Object* _other)
{

}

void GuardianAttackEffect::OnCollisionExit(Object* _other)
{

}
