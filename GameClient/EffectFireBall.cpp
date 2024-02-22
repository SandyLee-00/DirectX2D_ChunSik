#include "EffectFireBall.h"

EffectFireBall::EffectFireBall(ManagerSet* _managers)
	: Object("EffectFireBall", _managers, OBJECT_TYPE::ATTACHMENT, { 0, 0 })
	, isOn(false)
	, monster(nullptr)
	, animation(nullptr)
	, elapsedTime(0.0f)
{

}

EffectFireBall::~EffectFireBall()
{

}

void EffectFireBall::Start()
{
	animation = CreateComponent<Animation>();
	animation = GetComponent<Animation>();
	animation->SetOffset({0, 0});
	animation->SetSpriteRes(27, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void EffectFireBall::Update(float _deltaTime)
{
	auto* transform = GetComponent<Transform>();

	// ���̾ ����Ʈ isOn �Ǹ� ������ �ð� ������ Off �ϱ�
	if (isOn == true)
	{
		elapsedTime += _deltaTime;
		if (elapsedTime >= FIREBALL_EFFECTIME)
		{
			elapsedTime = 0.0f;
			isOn = false;
			SetState(OBJECT_STATE::DEAD);

		}
	}
}

void EffectFireBall::FinalUpdate(float _deltaTime)
{

}

void EffectFireBall::Render(GraphicsEngine* _graphicsEngine)
{
	const int OFFSET_Y = 85;

	if (isOn == true)
	{
		// ���̾ �������� �ִϸ��̼� ����ϱ�
		animation->SetSpriteRes(36, L"Animation\\Deal\\DealSkillEft.txt", "dealSkillEft", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y - OFFSET_Y);
	}
	else if (isOn == false)
	{
		// ���̾ �������� �ִϸ��̼� �� �̹����� �ٲٱ�
		animation->SetSpriteRes(27, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	}
	
}

void EffectFireBall::DebugRender(GraphicsEngine* _graphicsEngine)
{

}
