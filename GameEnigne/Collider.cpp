#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Collider::Collider(Object* _owner)
	: Component(CALL_ORDER::COLLIDER, "Collider", _owner)
	, id(index++)
	, isCollided(false)
	, shape(COLLIDER_SHPAE::END)
	, isActivate(true)
	, offset()
{
}

Collider::~Collider()
{
}

/// <summary>
/// 범용 충돌 체크
/// </summary>
/// <param name="_collider">충돌체</param>
/// <returns>충돌 결과</returns>
bool Collider::Collides(Collider* _collider)
{
	BoxCollider* box = dynamic_cast<BoxCollider*>(_collider);
	if (box != nullptr && this->IsCollision(box)) 
	{
		return true;
	}

	CircleCollider* circle = dynamic_cast<CircleCollider*>(_collider);
	if (circle != nullptr && this->IsCollision(circle))
	{
		return true;
	}

	assert(!(box == nullptr && circle == nullptr) && "Wrong Type To Compare Colliders");

	return false;
}

/// <summary>
/// 충돌체 아이디 값
/// </summary>
unsigned int Collider::index = 0;