#include "CollisionManager.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "AABBtree.h"

CollisionManager::CollisionManager()
	: checkMap{ 0, }
{

}

CollisionManager::~CollisionManager()
{
	delete aabbTree;
	for(auto& collision : this->collisions) 
	{
		delete collision.second;
	}
}

/// <summary>
/// 명시적 초기화
/// </summary>
/// <param name="_sceneManger">씬 매니져</param>
void CollisionManager::Initalize(SceneManager* _sceneManger)
{
	this->sceneManger = _sceneManger;
	this->aabbTree = new AABBTree(0.0f, this);
}

/// <summary>
/// 콜라이더 추가
/// </summary>
/// <param name="_input">추가할 콜라이더</param>
void CollisionManager::AddCollider(Collider* _input)
{
	this->aabbTree->AddCollider(_input);
}

/// <summary>
/// 충돌 업데이트
/// </summary>
void CollisionManager::Update()
{
	this->aabbTree->Update();

	std::list<std::pair<Collider*, Collider*>> pairs = this->aabbTree->GetCollisionPairs();

	SolveCollision(pairs);
}

/// <summary>
/// 디버깅 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void CollisionManager::DebugRender(GraphicsEngine* _graphicsEngine)
{
	this->aabbTree->DebugRender(_graphicsEngine);
}

/// <summary>
/// 충돌 맵 업데이트
/// </summary>
void CollisionManager::CheckCollisionMap()
{
	
}

/// <summary>
/// 충돌 업데이트
/// </summary>
void CollisionManager::UpdateCollision()
{
	// 모든 충돌에 대하여
	for(auto& c : this->collisions) 
	{
		// 충돌체 가져오기
		Collision* collision = c.second;
		Collider* a = collision->collider1;
		Collider* b = collision->collider2;

		// b 충돌체를 각각의 모양으로 다이나믹 캐스팅
		CircleCollider* cir = dynamic_cast<CircleCollider*>(b);
		BoxCollider* box = dynamic_cast<BoxCollider*>(b);

		// 캐스팅 결과와 충돌 여부를 파악
		if ((cir != nullptr && a->IsCollision(cir)) || 
			(box != nullptr && a->IsCollision(box))) 
		{
			// 충돌함
			collision->isCollisionNow = true;
		}
		else
		{
			// 충돌하지 않음
			collision->isCollisionNow = false;
		}
	}
}

/// <summary>
/// 충돌 해결
/// </summary>
void CollisionManager::SolveCollision(std::list<std::pair<Collider*, Collider*>> _pairs)
{
	// 모든 충돌에 대해
	for(auto& p : _pairs)
	{
		// 충돌 가져옴
		COLLIDER_KEY key = COLLIDER_KEY(p.first, p.second);
		std::map<COLLIDER_KEY, Collision*>::iterator collisionInfo = collisions.find(key);

		if (collisionInfo == collisions.end())
		{
			collisions.insert({ key, new Collision(p.first, p.second) });
		}
		else
		{
			collisionInfo->second->isCollisionNow = true;
		}	
	}

	for(auto& c : collisions) 
	{
		Collision* collision = c.second;

		// 만일 이전과 지금 둘 다 충돌하지 않았으면 무시
		if (!(collision->isCollisionNow || collision->isCollisionPast))
		{
			continue;
		}
		// 이전에 충돌했고 지금도 충돌함 (stay)
		else if (collision->isCollisionNow && collision->isCollisionPast)
		{
			collision->collider1->GetOwner()->OnCollisionStay(collision->collider2->GetOwner());
			collision->collider2->GetOwner()->OnCollisionStay(collision->collider1->GetOwner());
		}
		// 이전에 충돌 하지 않았고 지금은 함 (enter)
		else if (collision->isCollisionNow == true && collision->isCollisionPast == false)
		{
			collision->collider1->GetOwner()->OnCollisionEnter(collision->collider2->GetOwner());
			collision->collider2->GetOwner()->OnCollisionEnter(collision->collider1->GetOwner());
		}
		// 이전에 충돌 했고 지금은 아님 (ecit)
		else if (collision->isCollisionNow == false && collision->isCollisionPast == true)
		{
			collision->collider1->GetOwner()->OnCollisionExit(collision->collider2->GetOwner());
			collision->collider2->GetOwner()->OnCollisionExit(collision->collider1->GetOwner());
		}
		// 충돌 동기화
		collision->isCollisionPast = collision->isCollisionNow;
		collision->isCollisionNow = false;
	}
}

/// <summary>
/// 비트 플래그를 이용한 충돌 설정
/// </summary>
/// <param name="_a">오브젝트 타입</param>
/// <param name="_b">오브젝트 타입</param>
void CollisionManager::MarkCollisionType(OBJECT_TYPE _a, OBJECT_TYPE _b)
{
	// 비트 플래그 형식
	this->checkMap[(int)_a] |= 1 << (int)_b;
	this->checkMap[(int)_b] |= 1 << (int)_a;
}

/// <summary>
/// 총돌 가능한 타입인지
/// </summary>
/// <param name="_a">타입 1</param>
/// <param name="_b">타입 2</param>
/// <returns>충돌 가능 여부</returns>
bool CollisionManager::CheckType(OBJECT_TYPE _a, OBJECT_TYPE _b)
{
	return this->checkMap[(int)_a] & 1 << (int)_b;
}

/// <summary>
/// 모든 충돌 판정 0 으로 리셋
/// </summary>
void CollisionManager::ResetCollisoinType()
{
	for (int i = 0; i < (int)OBJECT_TYPE::END; i++)
	{
		this->checkMap[i] = 0;
	}
}

void CollisionManager::ResetCollison()
{
	for (auto& collision : this->collisions)
	{
		delete collision.second;
	}
	collisions.clear();
	collisions = std::map<COLLIDER_KEY, Collision*>();
}

void CollisionManager::DestroyAABBTree()
{
	this->aabbTree->Clear();
}
