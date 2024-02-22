#include "EffectSupporterMove.h"
#include "Supporter.h"

EffectSupporterMove::EffectSupporterMove(ManagerSet* _managers)
	: Object("EffectSupporterMove", _managers, OBJECT_TYPE::ATTACHMENT, { 0, 0 })
	, isOnOff(false)
	, supporter(nullptr)
	, animation(nullptr)
	, elapsedTime(0.f)
{

}

EffectSupporterMove::~EffectSupporterMove()
{

}

void EffectSupporterMove::Start()
{
	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ 0,0 });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void EffectSupporterMove::Update(float _deltaTime)
{
	auto transform = CreateComponent<Transform>();
	Vector2 supPos = supporter->GetComponent<Transform>()->GetPosition();
	Vector2 offset = { 0,0 };
	if (supporter->GetLookDirection() == DIRECTION::RIGHT)
	{
		offset = { -85,-10 };
	}
	if (supporter->GetLookDirection() == DIRECTION::LEFT)
	{
		offset = { 80,-5 };
	}

	transform->SetPosition(supPos + offset);

	elapsedTime += _deltaTime;
	if (elapsedTime >= 0.5f)
	{
		isOnOff = false;
		elapsedTime = 0.f;
		// SetState(OBJECT_STATE::DEAD);
	}
}

void EffectSupporterMove::FinalUpdate(float _deltaTime)
{

}

void EffectSupporterMove::Render(GraphicsEngine* _graphicsEngine)
{
	if (supporter->GetLookDirection() == DIRECTION::LEFT)
	{
		if (isOnOff)
		{
			animation->SetSpriteRes(34, L"Animation\\Sup\\SupMoveEftL.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		if (!isOnOff)
		{
			animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
	}
	if (supporter->GetLookDirection() == DIRECTION::RIGHT)
	{
		if (isOnOff)
		{
			animation->SetSpriteRes(35, L"Animation\\Sup\\SupMoveEftR.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		if (!isOnOff)
		{
			animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
	}
}

void EffectSupporterMove::DebugRender(GraphicsEngine* _graphicsEngine)
{

}
