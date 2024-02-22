#pragma once
#include "Component.h"
#include "Matrix.h"
class Object;
class BoxCollider;
class CircleCollider;
class GraphicsEngine;
class AABBNode;
/// <summry>
/// Collider 클래스
/// 최초 작성일 : 2023/07/24
/// 최초 작성일 : 2023/08/08
/// 작성자 : 김형환
/// 
/// 오브젝트의 충돌체 정보를 가지고 있는 클래스
/// CollisionManager 클래스에 의해 관리되어짐
/// 
/// 현재 박스와 원형 콜라이더 두 종류만 있음. 추후 필요시 추가 예정
/// 주인 오브젝트의 위치를 기반으로 생성된다
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

	// 콜라이더 업데이트, dt 필요 없음
	virtual void Update(float _dt = 0) abstract;
	// 콜라이더 렌더, 디버깅 렌더에서 사용할 함수
	virtual void Render(GraphicsEngine* _graphicsEngine) abstract;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) abstract;
	virtual void LateUpdate() override {};


	// 충돌 여부
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


/// 기태야 고마워
/// 콜라이더 충돌쌍을 가지고 Key값을 만든다
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

/// ColliderKey의 맵에서 사용하는 정렬알고리즘
inline bool operator <(const COLLIDER_KEY& colliderKey1, const COLLIDER_KEY& colliderKey2)
{
	if (colliderKey1.Key < colliderKey2.Key)
		return true;

	return false;
}