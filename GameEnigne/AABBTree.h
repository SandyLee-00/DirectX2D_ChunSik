#pragma once
#include "headers.h"
#include "AABBNode.h"
#include "AABB.h"

class CollisionManager;
class GraphicsEngine;

/// <summary>
/// 레이캐스트에 대한 결과
/// </summary>
struct RayCastResult
{
	bool hit;
	Collider* collider;
	Vector2 position;
	Vector2 normal;
};

class AABBTree
{
private:
	AABBNode* root;
	std::list<std::pair<Collider*, Collider*>> pairs;
	const float margin;

	CollisionManager* collisionManager;
	std::vector<AABBNode*> invalidNodes;
	std::vector<AABBNode*> removeNodes;

public:
	AABBTree(float _margin, CollisionManager* _collisionManager);
	~AABBTree();

	void AddCollider(Collider* _collider);
	void RemoveCollider(Collider* _collider);
	void Update();
	void Remove(Collider* _collider);
	std::list<std::pair<Collider*, Collider*>>& GetCollisionPairs();

	// 점과 충돌하는 충돌체들 반환
	void Pick(const Vector2& _point, std::vector<Collider*>& _colliderVector);

	// 사각형 내부에 충돌하는  Collider 반환
	void Query(const AABB& _aabb, std::vector<Collider*>& _output) const;

// 	RayCastResult RayCast(const Vector2& _direct
// 		, const Vector2& _center, float _maxDistance = 0.f) const;


	// 트리를 초기화한다.
	void Clear();

	void DebugRender(GraphicsEngine* _graphicsEngine);

private:
	void UpdateAllNode(AABBNode* _node);
	void InsertNode(AABBNode* _node, AABBNode** _parent);
	void RemoveNode(AABBNode* _node);
	void ComputeCollisionPairs(AABBNode* _n0, AABBNode* _n1);
	void ClearChildrenCrossFlag(AABBNode* _node);
	void CrossChildren(AABBNode* _node);


};

