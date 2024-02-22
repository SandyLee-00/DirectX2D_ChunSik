#pragma once
#include "headers.h"
#include "Collider.h"
class Collider;
class SceneManager;
class GraphicsEngine;
class AABBTree;

/// <summry>
/// CollisionManager 클래스
/// 최초 작성일 : 2023/07/25
/// 최초 작성일 : 2023/08/08
/// 작성자 : 김형환
/// 
/// 충돌 처리를 위한 클래스
/// 오브젝트를 가져오기 위해 일단 구현 보류 -> SceneManager 작성 후 거기서 오브젝트 가져올 예정
/// AABBTree 활용 방식으로 변경 23/08/08
/// <\summry>


class CollisionManager
{
private:
	// 충돌
	std::map<COLLIDER_KEY, Collision*> collisions;
	// 충돌 체크
	unsigned int checkMap[(int)OBJECT_TYPE::END];
	SceneManager* sceneManger;
	static unsigned int collisionId;
	AABBTree* aabbTree;

public:
	void Initalize(SceneManager* _sceneManger);

	void AddCollider(Collider* _input);
	void Update();
	void DebugRender(GraphicsEngine* _graphicsEngine);
	void CheckCollisionMap();
	void UpdateCollision();
	void SolveCollision(std::list<std::pair<Collider*, Collider*>> _pairs);

	void MarkCollisionType(OBJECT_TYPE _a, OBJECT_TYPE _b);
	bool CheckType(OBJECT_TYPE _a, OBJECT_TYPE _b);
	void ResetCollisoinType();

	void ResetCollison();

	void DestroyAABBTree();

	CollisionManager();
	~CollisionManager();
};

