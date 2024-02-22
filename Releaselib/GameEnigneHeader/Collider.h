#pragma once
#include "Component.h"
#include "Matrix.h"
class Object;
class BoxCollider;
class CircleCollider;
class GraphicsEngine;
class AABBNode;
/// <summry>
/// Collider Ŭ����
/// ���� �ۼ��� : 2023/07/24
/// ���� �ۼ��� : 2023/08/08
/// �ۼ��� : ����ȯ
/// 
/// ������Ʈ�� �浹ü ������ ������ �ִ� Ŭ����
/// CollisionManager Ŭ������ ���� �����Ǿ���
/// 
/// ���� �ڽ��� ���� �ݶ��̴� �� ������ ����. ���� �ʿ�� �߰� ����
/// ���� ������Ʈ�� ��ġ�� ������� �����ȴ�
/// <\summry>

class Collider :
	public Component
{
private:
	const unsigned int id;
	bool isCollided;
	static unsigned int index;
	bool isActivate;
	AABBNode* node;
	Vector2 offset;

protected:
	COLLIDER_SHPAE shape;

public:
	Collider(Object* _owner);
	virtual ~Collider();

	// �ݶ��̴� ������Ʈ, dt �ʿ� ����
	virtual void Update(float _dt = 0) abstract;
	// �ݶ��̴� ����, ����� �������� ����� �Լ�
	virtual void Render(GraphicsEngine* _graphicsEngine) abstract;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) abstract;
	virtual void LateUpdate() override {};


	// �浹 ����
	virtual bool IsCollision(BoxCollider* _other) abstract;
	virtual bool IsCollision(CircleCollider* _other) abstract;
	virtual bool IsCollision(Vector2 _other) abstract;

	bool GetIsActivate() const { return isActivate; }
	void SetIsActivate(bool val) { isActivate = val; }
	bool GetIsCollied() const { return isCollided; }
	void SetIsCollied(bool val) { isCollided = val; }
	const unsigned int GetId() const { return this->id; }

	virtual Vector2 GetMinPoint() abstract;
	virtual Vector2 GetMaxPoint() abstract;
	AABBNode* GetNode() const { return node; }
	void SetNode(AABBNode* val) { node = val; }

	bool Collides(Collider* _collider);
	Vector2 GetOffset() const { return offset; }
	void SetOffset(Vector2 val) { offset = val; }
};

class Collision
{
public:
	Collision(Collider* _collider1, Collider* _collider2)
		: collider1(_collider1)
		, collider2(_collider2)
		, isCollisionNow(true)
		, isCollisionPast(false)
	{
	}
	Collider* collider1;
	Collider* collider2;
	bool isCollisionNow;
	bool isCollisionPast;
};


/// ���¾� ����
/// �ݶ��̴� �浹���� ������ Key���� �����
union COLLIDER_KEY
{
	COLLIDER_KEY(Collider* _collider1, Collider* _collider2) :Key(0)
	{
		ColliderID1 = min(_collider1->GetId(), _collider2->GetId());
		ColliderID2 = max(_collider1->GetId(), _collider2->GetId());
	}

	struct
	{
		unsigned int ColliderID1;
		unsigned int ColliderID2;
	};

	unsigned long long Key;
};

/// ColliderKey�� �ʿ��� ����ϴ� ���ľ˰���
inline bool operator <(const COLLIDER_KEY& colliderKey1, const COLLIDER_KEY& colliderKey2)
{
	if (colliderKey1.Key < colliderKey2.Key)
		return true;

	return false;
}