#pragma once
#include "headers.h"
#include "Collider.h"
class Collider;
class SceneManager;
class GraphicsEngine;
class AABBTree;

/// <summry>
/// CollisionManager Ŭ����
/// ���� �ۼ��� : 2023/07/25
/// ���� �ۼ��� : 2023/08/08
/// �ۼ��� : ����ȯ
/// 
/// �浹 ó���� ���� Ŭ����
/// ������Ʈ�� �������� ���� �ϴ� ���� ���� -> SceneManager �ۼ� �� �ű⼭ ������Ʈ ������ ����
/// AABBTree Ȱ�� ������� ���� 23/08/08
/// <\summry>


class CollisionManager
{
private:
	// �浹
	std::map<COLLIDER_KEY, Collision*> collisions;
	// �浹 üũ
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

