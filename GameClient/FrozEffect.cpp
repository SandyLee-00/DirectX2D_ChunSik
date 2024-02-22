#include "FrozEffect.h"
#include "Monster.h"

FrozEffect::FrozEffect(ManagerSet* _managers)
	: Object("FrozEffect", _managers, OBJECT_TYPE::ATTACHMENT, { 0,0 })
	, animation(nullptr)
	, isOnOff(false)
	, elapsedTime(0.f)
	, monster(nullptr)
{

}

FrozEffect::~FrozEffect()
{

}

void FrozEffect::Start()
{
	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ 0,0 });
	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void FrozEffect::Update(float _deltaTime)
{
	auto transform = CreateComponent<Transform>();
	Vector2 monPos = monster->GetComponent<Transform>()->GetPosition();
	Vector2 offset = { 0,0 };
	transform->SetPosition(monPos + offset);

	elapsedTime += _deltaTime;
	if (elapsedTime >= 1.8f)
	{
		isOnOff = false;
		elapsedTime = 0.f;
	}
}

void FrozEffect::FinalUpdate(float _deltaTime)
{

}

void FrozEffect::Render(GraphicsEngine* _graphicsEngine)
{
	if (isOnOff)
	{
		animation->SetSpriteRes(72, L"Animation\\frozEft.txt", "frozEft", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}
	if (!isOnOff)
	{
		animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}
}

void FrozEffect::DebugRender(GraphicsEngine* _graphicsEngine)
{

}

void FrozEffect::OnCollisionEnter(Object* _other)
{

}

void FrozEffect::OnCollisionStay(Object* _other)
{

}

void FrozEffect::OnCollisionExit(Object* _other)
{

}
