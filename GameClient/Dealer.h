#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// 
/// 1. 몬스터 전체 다 죽이기
/// 2. 서포터 실드 받기
/// 3. 죽으면 게임 끝
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
	// 밸런스 시트 const 값들

	// 딜러 체력
	const int MAXHP = 5;
	// 딜러 체력 감소 수치
	const int HP_DEC = 1;
	// 딜러 체력 감소 수치 (서포터 쉴드)
	const int HP_DEC_SHIELD = 0;

	// ATTACK 애니메이션 재생 시간
	const float ATTACKTIME = 5.2f;

	// TODO : 오브젝트로 따로 뺴기
	// 서포터 쉴드 유지 시간
	const float SUPPORTER_SHIELD_MAXTIME = 4.0f;

	const float HIT_EFFECTTIME = 0.5f;

	// 딜러Z스택
	const int MAXZ = 5;

	// 밸런스 시트 const 값들
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
	//실드를 했는가?
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

