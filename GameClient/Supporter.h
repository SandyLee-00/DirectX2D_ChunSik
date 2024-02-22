#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// �̼���
/// 
/// 1. ���� �󸮱�
/// 2. ����� / ���� �ǵ� �ɱ�
/// 3. ������ ���� ��
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
	// �뷱�� ��Ʈ const ����

	// ������ ĳ���� �̵� �ð�
	const float MOVETIME = 0.15f;
	// �̵� �ִϸ��̼� ��� �ð�
	const float MOVE_ANIMTIME = 0.5f;

	// Ȥ�� �� ��ȹ�� ���ϴ� ������ �̵� ������
	const float MOVE_DELAY = 0.0f;

	// ������ ü��
	const int MAXHP = 5;
	// ������ ü�� ���� ��ġ
	const int HP_DEC = 1;

	// ������ ���� ��Ÿ��
	const float SUPPORTERSHIELD_COOLTIME = 6.0f;

	// ������ ���� �� �ִ� ��
	const int SUPPORTER_SHIELD_BAR_MAX = 6;

	// ������ HIT effect / anim
	const float HIT_EFFECTTIME = 0.5f;

	// ������ SHIELD effect / anim
	const float SHIELD_EFFECTTIME = 0.6f;

	// �뷱�� ��Ʈ const ����
	// -----------------------------------

	// MOVE
	float elapedmoveDelayTime;

	SUPPORTER_STATE currentState;
	SUPPORTER_STATE previousState;
	// TODO: prevState�� �ٲٱ�
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

	// �ǵ� �� �� �׸���
	int shieldCoolTimeBarValue;

	// -----------------------------------

	Animation* animation;
	// -----------------------------------
	// ChildObjects
	RangeSupporterSheild* supporterSheildRange;
	FrozEffect* frozEffect;
	EffectSupporterMove* supMoveEft;

	// TODO: Child-Parent ����� �ٲٱ�
	// std::vector<Object*> childObjects;
	// 
	// TODO: Object ��ü���� Child-Parent ���� �����

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
