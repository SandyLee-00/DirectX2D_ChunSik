#include "MonsterSpawner.h"
#include "Monster.h"
#include "Grid.h"
#include "FrozEffect.h"
#include "GuardianAttackEffect.h"

MonsterSpawner::MonsterSpawner(ManagerSet* _managers)
	: Object("MonsterSpawner", _managers, OBJECT_TYPE::BACK_GROUND, { 0, 0 })
	, spawnPositions{}
	, moveElapsedTime(0.0f)
	, nextMonsterUID(0)
	, monsterPool(nullptr)
	, DZ(nullptr)
	, TF(nullptr)
{
	this->SetCanPause(true);
}

MonsterSpawner::~MonsterSpawner()
{

}

void MonsterSpawner::Start()
{
	moveElapsedTime = 0.0f;

	nextMonsterUID = 0;

	for (int i = 0; i < 6; i++)
	{
		this->spawnPositions.push_back({ i, 10 });
	}

	for (int i = 15; i < 20; i++)
	{
		this->spawnPositions.push_back({ i, 10 });
	}

	for (int i = 0; i < 10; i++)
	{
		this->spawnPositions.push_back({ 0, i });
		this->spawnPositions.push_back({ 20, i });
	}
}

void MonsterSpawner::Update(float _deltaTime)
{
	// SPAWNTIME 마다 몬스터 생성
	moveElapsedTime += _deltaTime;
	if (moveElapsedTime >= SPAWNTIME)
	{
		moveElapsedTime = 0.0f;
		SpawnMonster();
	}
}

void MonsterSpawner::FinalUpdate(float _deltaTime)
{

}

void MonsterSpawner::Render(GraphicsEngine* _graphicsEngine)
{

}

void MonsterSpawner::DebugRender(GraphicsEngine* _graphicsEngine)
{

}

void MonsterSpawner::SpawnMonster()
{
	// 몬스터 생성 개수 랜덤으로 설정(1~5)
	int spawnedCount = random::GetRandom<int>(MIN_SPAWN_COUNT, MAX_SPAWN_COUNT);

	for (int i = 0; i < spawnedCount; i++)
	{
		// 몬스터 생성
		Monster* monster = GetMonsterPool()->GetObject();
		monster->SetGameState(MONSTER_STATE::IDLE);
		monster->SetMonsterPool(monsterPool);
		GetManagers()->GetSceneManager()->AddObject(monster);

		FrozEffect* frozEffect = new FrozEffect(GetManagers());
		monster->SetFrozEffect(frozEffect);
		frozEffect->SetMonster(monster);
		GetManagers()->GetSceneManager()->AddObject(frozEffect);

		GuardianAttackEffect* gdnAtkEft = new GuardianAttackEffect(GetManagers());
		monster->SetGdnAtkEft(gdnAtkEft);
		gdnAtkEft->SetMonster(monster);
		GetManagers()->GetSceneManager()->AddObject(gdnAtkEft);

		monster->SetDZ(DZ);
		monster->SetTF(TF);

		// 몬스터 위치 랜덤으로 설정
		int spawnPosIdx = random::GetRandom<int>(0, spawnPositions.size() - 1);
		POINT spawnPos = spawnPositions[spawnPosIdx];
		Transform* monsterTransform = monster->GetComponent<Transform>();
		monsterTransform->SetPosition(Grid::GetPostion(spawnPos.x, spawnPos.y));
		monster->SetPostionInGrid(spawnPos);

		// 몬스터 타입 랜덤으로 설정
		int monsterType = random::GetRandom<int>(0, MAX_MONSTER_TYPE);
		if (monsterType == 0)
		{
			monster->SetMonsterType(MONSTER_TYPE::TWO);
			monster->SetStopTime(2.0f);
		}
		else if (monsterType == 1)
		{
			monster->SetMonsterType(MONSTER_TYPE::THREE);
			monster->SetStopTime(3.0f);
			monster->SetMoveSpeed(96.f / 0.3f);
		}

		// 몬스터 UID 설정
		monster->SetUID(nextMonsterUID);

		// 몬스터 Score 데이터 초기화
		monster->SetInitDataZero();

		nextMonsterUID++;
	}
}
