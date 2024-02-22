#include "RangeGuardianAttack.h"
#include "Monster.h"
#include "Supporter.h"
#include "Guardian.h"
#include "GuardianAttackEffect.h"

RangeGuardianAttack::RangeGuardianAttack(ManagerSet* _managers)
	: Object("RangeGuardianAttack", _managers, OBJECT_TYPE::ATTACHMENT, { 0, 0})
	, elapsedTime(0.f)
{
	parent = nullptr;
	isOnOff = false;
}

RangeGuardianAttack::~RangeGuardianAttack()
{

}

void RangeGuardianAttack::Start()
{
	// �ǵ� ���� collider ����
	auto collider = CreateComponent<BoxCollider>();
	collider->SetOffset({-96,0});
	collider->SetSize(ATTACK_RANGE);
	this->GetManagers()->GetCollisionManager()->AddCollider(collider);

}

void RangeGuardianAttack::Update(float _deltaTime)
{
	// OnOff ����𿡼� �ϱ�

	// ��ġ�� ������Ʈ
	auto transfrom = GetComponent<Transform>();
	auto parentPosition = parent->GetComponent<Transform>()->GetPosition();

	// Offset��ŭ �θ𿡼� ������ ��ġ�� ����
	Vector2 offset = { 0, 0 };
	transfrom->SetPosition(parentPosition + offset);

	if (isOnOff)
	{
		elapsedTime += _deltaTime;
		if (elapsedTime >= ATTACKTIME + 1.f)
		{
			isOnOff = false;
			elapsedTime = 0.f;
		}
	}

}

void RangeGuardianAttack::FinalUpdate(float _deltaTime)
{

}

void RangeGuardianAttack::Render(GraphicsEngine* _graphicsEngine)
{
	
}

void RangeGuardianAttack::DebugRender(GraphicsEngine* _graphicsEngine)
{
	// �������� ���� �׸���
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "RangeGuardianAttack";

	if (isOnOff == true)
	{
		stateString += "On";
		Vector2 tmp = ATTACK_RANGE + position;
		//_graphicsEngine->DrawRectangle(position.x, position.y, tmp.x, tmp.y);
	}
	else if (isOnOff == false)
	{
		stateString += "Off";
	}

	_graphicsEngine->DrawString((int)position.x, (int)position.y - 30, stateString);
}

void RangeGuardianAttack::OnCollisionEnter(Object* _other)
{
	
}

void RangeGuardianAttack::OnCollisionStay(Object* _other)
{
	// ����� ���� �������� ��
	// 1. ���Ϳ� �浹���� ��
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		assert(monster && "cannot find monster\n");

		Guardian* guardian = dynamic_cast<Guardian*>(parent);
		assert(guardian && "cannot find guardian\n");

		// 1-1. ���Ͱ� (IDLE || MOVE || HOLD) ������ �� && ����� ���� ���� OFF && ����� ���� ��Ÿ���� ������ �� && ������� IDLE ������ ��
		// -> ����� ���� ���� ON
		// -> ����� ���� ATTACK���� �ٲٱ�
		if ((monster->GetGameState() == MONSTER_STATE::IDLE || monster->GetGameState() == MONSTER_STATE::MOVE || monster->GetGameState() == MONSTER_STATE::HOLD) &&
			isOnOff == false &&
			guardian->GetAttackCoolTime() >= ATTACK_COOLTIME &&
			guardian->GetGameState() == GUARDIAN_STATE::IDLE
			)
		{
			isOnOff = true;
			guardian->SetGameState(GUARDIAN_STATE::ATTACK);
			monster->GetGdnAtkEft()->SetOnOff(true);
		}
	}


	// ������� ���� ���ϰ� ������ ����
	if (isOnOff == false)
	{
		return;
	}

	// ����� ���� �������� ��
	// 1. ����� ���� ������ ���Ϳ� �浹�� ���·� �����Ǵ� ����
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		assert(monster && "cannot find monster\n");

		Guardian* guardian = dynamic_cast<Guardian*>(parent);
		assert(guardian && "cannot find guardian\n");

		// 1-1. ���Ͱ� IDLE ������ �� || ���Ͱ� MOVE ������ ��
		// -> ���� ���� DEAD�� �ٲٱ�
		if (monster->GetGameState() == MONSTER_STATE::IDLE ||
			monster->GetGameState() == MONSTER_STATE::MOVE || monster->GetGameState() == MONSTER_STATE::HOLD)
		{
			if (monster->GetGameState() == MONSTER_STATE::HOLD)
			{
				monster->SetGameState(MONSTER_STATE::HOLD_DEAD_READY);
				monster->SetGdnHit(true);
			}
			else
			{
				monster->SetGameState(MONSTER_STATE::DEAD_READY);
				monster->SetGdnHit(true);
			}
		}
	}
	
}

void RangeGuardianAttack::OnCollisionExit(Object* _other)
{

}
