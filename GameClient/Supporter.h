#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// 이서영
/// 
/// 1. 몬스터 얼리기
/// 2. 가디언 / 딜러 실드 걸기
/// 3. 죽으면 게임 끝
/// </summary>

class RangeSupporterSheild;
class BarHP;
class ShieldToDealer;
class FrozEffect;
class EffectSupporterMove;

class Supporter
	: public Object
{
private:
	// -----------------------------------
	// 밸런스 시트 const 값들

	// 서포터 캐릭터 이동 시간
	const float MOVETIME = 0.15f;
	// 이동 애니메이션 출력 시간
	const float MOVE_ANIMTIME = 0.5f;

	// 혹시 모를 기획이 원하는 서포터 이동 딜레이
	const float MOVE_DELAY = 0.0f;

	// 서포터 체력
	const int MAXHP = 5;
	// 서포터 체력 감소 수치
	const int HP_DEC = 1;

	// 서포터 쉴드 쿨타임
	const float SUPPORTERSHIELD_COOLTIME = 6.0f;

	// 서포터 가드 바 최대 값
	const int SUPPORTER_SHIELD_BAR_MAX = 6;

	// 서포터 HIT effect / anim
	const float HIT_EFFECTTIME = 0.5f;

	// 서포터 SHIELD effect / anim
	const float SHIELD_EFFECTTIME = 0.6f;

	// 밸런스 시트 const 값들
	// -----------------------------------

	// MOVE
	float elapedmoveDelayTime;

	SUPPORTER_STATE currentState;
	SUPPORTER_STATE previousState;
	// TODO: prevState로 바꾸기
	bool isMove;
	
	DIRECTION nextDirection;
	DIRECTION lookDirection;

	int HP;
	float moveSpeed;
	float elapsedDistance;
	POINT positionInGrid;

	// HIT
	float hitElapsedTime;

	// SHIELD
	float shieldCoolTime;
	bool isShieldReady;
	float shieldElapsedTime;

	// DEAD
	float deadAniElapsedTime;
	bool isDead;

	// 실드 쿨 바 그리기
	int shieldCoolTimeBarValue;

	// -----------------------------------

	Animation* animation;
	// -----------------------------------
	// ChildObjects
	RangeSupporterSheild* supporterSheildRange;
	FrozEffect* frozEffect;
	EffectSupporterMove* supMoveEft;

	// TODO: Child-Parent 관계로 바꾸기
	// std::vector<Object*> childObjects;
	// 
	// TODO: Object 자체에서 Child-Parent 관계 만들기

	// -----------------------------------

public:
	Supporter(ManagerSet* _managers);
	~Supporter();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void UpdateIDLE(float _deltaTime);
	void UpdateMOVE(float _deltaTime);
	void UpdateHIT(float _deltaTime);
	void UpdateHOLD(float _deltaTime);
	void UpdateSHIELD(float _deltaTime);
	void UpdateDEAD(float _deltaTime);

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetGameState(SUPPORTER_STATE _state) { currentState = _state; };
	SUPPORTER_STATE GetGameState() { return currentState; };

	void SetRangeSupporterSheild(RangeSupporterSheild* _rangeSupporterSheild) { supporterSheildRange = _rangeSupporterSheild; };
	
	int GetHP() { return HP; };

	DIRECTION GetLookDirection() { return lookDirection; };

	FrozEffect* GetFrozEffect() const { return frozEffect; }
	void SetFrozEffect(FrozEffect* val) { frozEffect = val; }
	EffectSupporterMove* GetSupMoveEft() const { return supMoveEft; }
	void SetSupMoveEft(EffectSupporterMove* val) { supMoveEft = val; }

	int GetShieldCoolTimeBarValue() const { return shieldCoolTimeBarValue; }

private:
	bool CheckMoveable(float _x, float _y);

};
