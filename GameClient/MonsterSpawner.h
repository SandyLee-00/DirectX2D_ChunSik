#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// �̼���
/// 
/// ���� ���� �ֱ⿡ ���� ���͸� ����
/// </summary>

class BackGroundObject;
class Monster;
class BarDealerZ;
class TextFrozenCount;

class MonsterSpawner
	: public Object
{
private:
	// -----------------------------------
	// �뷱�� ��Ʈ const ����
	
	// ���� ���� �ֱ�
	const float SPAWNTIME = 4.0f;

	// ���� ���� ���� �� 
	// 0~5 ����
	const int MIN_SPAWN_COUNT = 1;
	const int MAX_SPAWN_COUNT = 7;

	const int MAX_MONSTER_TYPE = 2;

	std::vector<POINT> spawnPositions;

	const int GRID_SIZE = 96;

	// �뷱�� ��Ʈ const ����
	// -----------------------------------
	float moveElapsedTime;
	int nextMonsterUID;

	ObjectPool<Monster, 100>* monsterPool;

	BarDealerZ* DZ;
	TextFrozenCount* TF;

public:
	MonsterSpawner(ManagerSet* _managers);
	~MonsterSpawner();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SpawnMonster();

	ObjectPool<Monster, 100>* GetMonsterPool() const { return monsterPool; }
	void SetMonsterPool(ObjectPool<Monster, 100>* val) { monsterPool = val; }
	BarDealerZ* GetDZ() const { return DZ; }
	void SetDZ(BarDealerZ* val) { DZ = val; }
	TextFrozenCount* GetTF() const { return TF; }
	void SetTF(TextFrozenCount* val) { TF = val; }
};

