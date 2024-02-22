#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// �̼���
/// 
/// 1. ���� �߰��ؼ� ����
/// 2. ������ �ǵ� �ޱ�
/// 3. ������ �ǵ� �ɱ�
/// 4. ������ ���� ��
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
	// �뷱�� ��Ʈ const ����

	// ����� ü��
	const int MAXHP = 5;

	// ����� ���� ��� �ֱ�
	const float GURDIAN_SHIELD_COOLTIME = 10.f;

	// ����� ���� �� �ִ� ��
	const int GURDIAN_SHIELD_BAR_MAX = 5;

	// ����� ���� ���� �ð�
	const float GURDIAN_SHIELD_MAXTIME = 8.0f;

	// ����� ���� �ð�
	const float STOPTIME = 0.7f;

	// ����� �̵� �ð�
	const float MOVETIME = 0.15f;

	// ����� ���� ��Ÿ��
	const float ATTACK_COOLTIME = 3.0f;

	// ����� ���� �ð�
	const float ATTACKTIME = 0.9f;

	// ����� HIT effect / anim
	const float HIT_EFFECTTIME = 0.6f;

	// ����� DEAD effect / anim
	const float DEAD_EFFECTTIME = 6.0f;

	// �뷱�� ��Ʈ const ����
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
	// ���� ��Ÿ��
	float elapsedAttackTime;
	float elapsedAttackReadyTime;

	// HIT
	float hitElapsedTime;

	//Shield
	//�ǵ带 �ߴ°�?
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
	// UI ���̾�� �÷��� �ؼ� ���� �����ֱ�
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
