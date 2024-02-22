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
	// 실드 범위 collider 생성
	auto collider = CreateComponent<BoxCollider>();
	collider->SetOffset({-96,0});
	collider->SetSize(ATTACK_RANGE);
	this->GetManagers()->GetCollisionManager()->AddCollider(collider);

}

void RangeGuardianAttack::Update(float _deltaTime)
{
	// OnOff 가디언에서 하기

	// 위치만 업데이트
	auto transfrom = GetComponent<Transform>();
	auto parentPosition = parent->GetComponent<Transform>()->GetPosition();

	// Offset만큼 부모에서 떨어진 위치로 설정
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
	// 가디언공격 범위 그리기
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
	// 가디언 공격 꺼져있을 때
	// 1. 몬스터와 충돌했을 때
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		assert(monster && "cannot find monster\n");

		Guardian* guardian = dynamic_cast<Guardian*>(parent);
		assert(guardian && "cannot find guardian\n");

		// 1-1. 몬스터가 (IDLE || MOVE || HOLD) 상태일 때 && 가디언 공격 범위 OFF && 가디언 공격 쿨타임이 지났을 때 && 가디언이 IDLE 상태일 때
		// -> 가디언 공격 범위 ON
		// -> 가디언 상태 ATTACK으로 바꾸기
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


	// 가디언이 공격 안하고 있으면 리턴
	if (isOnOff == false)
	{
		return;
	}

	// 가디언 공격 켜져있을 때
	// 1. 가디언 공격 범위가 몬스터와 충돌한 상태로 유지되는 동안
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		assert(monster && "cannot find monster\n");

		Guardian* guardian = dynamic_cast<Guardian*>(parent);
		assert(guardian && "cannot find guardian\n");

		// 1-1. 몬스터가 IDLE 상태일 때 || 몬스터가 MOVE 상태일 때
		// -> 몬스터 상태 DEAD로 바꾸기
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
