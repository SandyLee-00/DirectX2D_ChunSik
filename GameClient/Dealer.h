#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// 
/// 1. ���� ��ü �� ���̱�
/// 2. ������ �ǵ� �ޱ�
/// 3. ������ ���� ��
/// </summary>

class ShieldToDealer;
class BarHP;
class BarDealerZ;
class RangeGuardianAttack;

class Dealer
	: public Object
{
private:
	// -----------------------------------
	// �뷱�� ��Ʈ const ����

	// ���� ü��
	const int MAXHP = 5;
	// ���� ü�� ���� ��ġ
	const int HP_DEC = 1;
	// ���� ü�� ���� ��ġ (������ ����)
	const int HP_DEC_SHIELD = 0;

	// ATTACK �ִϸ��̼� ��� �ð�
	const float ATTACKTIME = 5.2f;

	// TODO : ������Ʈ�� ���� ����
	// ������ ���� ���� �ð�
	const float SUPPORTER_SHIELD_MAXTIME = 4.0f;

	const float HIT_EFFECTTIME = 0.5f;

	// ����Z����
	const int MAXZ = 5;

	// �뷱�� ��Ʈ const ����
	// -----------------------------------

	DEALER_STATE dealerState;
	int HP;
	//bool isShield;
	//int Z;
	float cutSceneTime;

	// ATTACK
	float attackElapsedTime;

	// GetHit
	float getHitElapsedTime;

	// Dead
	float deadAniElapsedTime;
	bool isDead;

	bool lastAttack;

	// -----------------------------------
	// ChildObjects
	ShieldToDealer* supporterShield;
	RangeGuardianAttack* attackRange;

	BarHP* hpBar;
	BarDealerZ* zBar;

	//Shield
	//�ǵ带 �ߴ°�?
	bool isSupShield;
	float shieldTime;

	// -----------------------------------

	Animation* animation;
public:
	Dealer(ManagerSet* _managers);
	~Dealer();

	void Start() override;
	void Update(float _deltaTime) override;

	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetGameState(DEALER_STATE _state) { dealerState = _state; };
	DEALER_STATE GetGameState() { return dealerState; };

	int GetHP() const { return HP; };
	void SetHP(int _hp) { HP = _hp; }

	float GetCutSceneTime() const { return cutSceneTime; }
	void SetCutSceneTime(float val) { cutSceneTime = val; }

	bool GetSupShield() const { return isSupShield; }
	void SetSupShield(bool val) { isSupShield = val; }
	void SetChild(RangeGuardianAttack* _rangeGuardianAttack) { attackRange = _rangeGuardianAttack; }
	void SetChild(BarDealerZ* _barDealerZ) { zBar = _barDealerZ; }
	void SetChild(ShieldToDealer* _supporterShield) { supporterShield = _supporterShield; }

	bool LastAttack() const { return lastAttack; }
	void LastAttack(bool val) { lastAttack = val; }
private:
	void UpdateIDLE(float _deltaTime);
	void UpdateATTACK(float _deltaTime);
	void UpdateHIT(float _deltaTime);
	void UpdatePROTECTED(float _deltaTime);
	void UpdateDEAD(float _deltaTime);

};

