#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// 이서영
/// 
/// 1. 몬스터 추격해서 공격
/// 2. 서포터 실드 받기
/// 3. 스스로 실드 걸기
/// 4. 죽으면 게임 끝
/// </summary>

class RangeGuardianAttack;
class ShieldToGuardian;
class ShieldFromGuardian;
class Monster;
class BarHP;
class Supporter;

class Guardian
	: public Object
{
private:
	// -----------------------------------
	// 밸런스 시트 const 값들

	// 가디언 체력
	const int MAXHP = 5;

	// 가디언 가드 사용 주기
	const float GURDIAN_SHIELD_COOLTIME = 10.f;

	// 가디언 가드 바 최대 값
	const int GURDIAN_SHIELD_BAR_MAX = 5;

	// 가디언 가드 유지 시간
	const float GURDIAN_SHIELD_MAXTIME = 8.0f;

	// 가디언 정지 시간
	const float STOPTIME = 0.7f;

	// 가디언 이동 시간
	const float MOVETIME = 0.15f;

	// 가디언 공격 쿨타임
	const float ATTACK_COOLTIME = 3.0f;

	// 가디언 공격 시간
	const float ATTACKTIME = 0.9f;

	// 가디언 HIT effect / anim
	const float HIT_EFFECTTIME = 0.6f;

	// 가디언 DEAD effect / anim
	const float DEAD_EFFECTTIME = 6.0f;

	// 밸런스 시트 const 값들
	// -----------------------------------

	GUARDIAN_STATE guardianState;
	DIRECTION nextDirection;
	DIRECTION lookDirection;
	POINT postionInGrid;

	// HIT
	int HP;

	// MOVE
	float moveSpeed;
	float elapsedDistance;

	// MOVE - Monster Targeting
	Monster* targetMonster;
	int targetMonsterUID;

	// IDLE
	float moveElapsedTime;

	// ATTACK
	// 공격 쿨타임
	float elapsedAttackTime;
	float elapsedAttackReadyTime;

	// HIT
	float hitElapsedTime;

	//Shield
	//실드를 했는가?
	bool isGuardianShield;
	bool isSupporterShield;

	float guardianShielElapsedTime;
	float supporterShieldElapsedTime;
	float shieldCoolTime;

	// DEAD
	float deadElapsedTime;
	bool isDead = false;

	Animation* animation;

	Supporter* supporter;
	
	// -----------------------------------
	// ChildObjects
	RangeGuardianAttack* attackRange; 

	ShieldFromGuardian* guardianShield;
	ShieldToGuardian* supporterShield;

	BarHP* hpBar;
	// UI 레이어로 올려야 해서 값만 전해주기
	int shieldCoolTimeBarValue;
	// -----------------------------------

public:
	Guardian(ManagerSet* _managers);
	~Guardian();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetGameState(GUARDIAN_STATE _state) { guardianState = _state; };
	GUARDIAN_STATE GetGameState() { return guardianState; };

	POINT GetPostionInGrid() const { return postionInGrid; }
	void SetPostionInGrid(POINT val) { postionInGrid = val; }

	int GetHP() const { return HP; }
	void SetHP(int _hp) { HP = _hp; }

	void SetAttackCoolTime(float _elapsedAttackTime) { elapsedAttackReadyTime = _elapsedAttackTime; }
	float GetAttackCoolTime() { return elapsedAttackReadyTime; }

	bool GetShield() const { return isGuardianShield; }
	void SetShield(bool val) { isGuardianShield = val; }
	bool GetSupShield() const { return isSupporterShield; }
	void SetSupShield(bool val) { isSupporterShield = val; }
	void SetChild(RangeGuardianAttack* _rangeGuardianAttack) { attackRange = _rangeGuardianAttack; }
	void SetChild(ShieldToGuardian* _supporterShield) { supporterShield = _supporterShield; }
	void SetChild(ShieldFromGuardian* _guardianShield) { guardianShield = _guardianShield; }

	void SetTargetSupporter(Supporter* val) { supporter = val; }

	int GetShieldCoolTimeBarValue() const { return shieldCoolTimeBarValue; }

	void SetTargetMonster(Monster* val) { targetMonster = val; }
private:
	void UpdateIDLE(float _deltaTime);
	void UpdateMOVE(float _deltaTime);
	void UpdateATTACK(float _deltaTime);
	void UpdateHIT(float _deltaTime);
	void UpdateDEAD(float _deltaTime);

private:
	void FindTargetMonster();
	bool CheckMoveable(float _x, float _y);
};
