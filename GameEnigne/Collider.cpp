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
/// ���� �浹 üũ
/// </summary>
/// <param name="_collider">�浹ü</param>
/// <returns>�浹 ���</returns>
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
/// �浹ü ���̵� ��
/// </summary>
unsigned int Collider::index = 0;