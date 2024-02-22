#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Dealer;
class Guardian;
class Supporter;
class FrozEffect;
class GuardianAttackEffect;
class BarDealerZ;
class TextFrozenCount;

class Monster
	: public Object
{
private:
	// -----------------------------------
	// �뷱�� ��Ʈ const ����

	// ����A ���� �ð�
	const float TWO_STOPTIME = 0.6f;

	// ����B ���� �ð�
	const float THREE_STOPTIME = 0.8f;

	// ���� �̵� �ð�
	const float TWO_MOVETIME = 0.2f;
	const float THREE_MOVETIME = 0.4f;

	// ���� ���̾�� �±� �� ��� �ð�
	const float DEAD_FIREBALL_READYTIME = 1.5f;

	// ���� �״� �ִϸ��̼� ��� �ð�
	const float DEADTIME = 0.5f;

	// ���� ���� ����Ʈ ��� �ð�
	const float EACH_MONSTER_SCORE_EFFECTIME = 7.0f;

	// �׸��� ������
	const float GRID_SIZE = 96.f;

	// �뷱�� ��Ʈ const ����
	// -----------------------------------

	MONSTER_STATE monsterState;
	DIRECTION nextDirection;
	DIRECTION lookDirection;

	MONSTER_TYPE monsterType;
	int UID;
	POINT postionInGrid;
	ObjectPool<Monster, 100>* monsterPool;
	Animation* animation = nullptr;

	// IDLE
	float OWNSTOPTIME;
	float moveElapsedTime;

	// MOVE
	float moveSpeed;
	float elapsedDistance;

	// DEAD_READY : ���̾�� �±� �� ���
	float deadReadyElapsedTime;
	bool isScoreOn;
	float elapsedTime;
	UINT64 eachMonsterScore;

	// DEAD
	float deadElapsedTime;
	bool getGdnHit;
	float getGdnHitTime;

	// HOLD
	FrozEffect* frozEffect;
	GuardianAttackEffect* gdnAtkEft;

	bool pastFrozen;

	BarDealerZ* DZ;
	TextFrozenCount* TF;

public:
	Monster(ManagerSet* _managers);
	~Monster();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetGameState(MONSTER_STATE _state) { monsterState = _state; };
	MONSTER_STATE GetGameState() { return monsterState; };

	void SetNextDirection(DIRECTION _direction) { nextDirection = _direction; };
	DIRECTION GetNextDirection() { return nextDirection; };

	void SetUID(int _uid) { UID = _uid; };
	int GetUID() { return UID; };

	void SetMonsterType(MONSTER_TYPE _monsterType) { monsterType = _monsterType; };
	void SetStopTime(float _stopTime) { OWNSTOPTIME = _stopTime; };

	POINT GetPostionInGrid() const { return postionInGrid; }
	void SetPostionInGrid(POINT val) { postionInGrid = val; }

	ObjectPool<Monster, 100>* GetMonsterPool() const { return monsterPool; }
	void SetMonsterPool(ObjectPool<Monster, 100>* val) { monsterPool = val; }

	void SetMoveSpeed(float val) { moveSpeed = val; }

	FrozEffect* GetFrozEffect() const { return frozEffect; }
	void SetFrozEffect(FrozEffect* val) { frozEffect = val; }

	void SetScoreOn(bool _isScoreOn) { isScoreOn = _isScoreOn; }
	void SetEachMonsterScore(UINT64 _eachMonsterScore) { eachMonsterScore = _eachMonsterScore; }

	void SetInitDataZero() { elapsedTime = 0.f; eachMonsterScore = 0; isScoreOn = false; }

	GuardianAttackEffect* GetGdnAtkEft() const { return gdnAtkEft; }
	void SetGdnAtkEft(GuardianAttackEffect* val) { gdnAtkEft = val; }
	bool GetGdnHit() const { return getGdnHit; }
	void SetGdnHit(bool val) { getGdnHit = val; }
	BarDealerZ* GetDZ() const { return DZ; }
	void SetDZ(BarDealerZ* val)
	{
		//if (DZ == nullptr)
		{
			DZ = val;
		}
	}

	TextFrozenCount* GetTF() const { return TF; }
	void SetTF(TextFrozenCount* val)
	{
		//if (TF == nullptr)
		{
			TF = val;
		}
	}

private:
	void UpdateMOVE(float _deltaTime);
	void UpdateIDLE(float _deltaTime);
	void UpdateDEAD_READY(float _deltaTime);
	void UpdateHOLD_DEAD_READY(float _deltaTime);
	void UpdateDEAD(float _deltaTime);
	void UpdateHOLD(float _deltaTime);


};
