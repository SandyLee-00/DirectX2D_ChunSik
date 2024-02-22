#include "AABB.h"
#include "Collider.h"

AABB::AABB()
{

}

AABB::AABB(const Vector2& _minPoint, const Vector2& _maxPoint)
{

}

/// <summary>
/// 두 AABB를 합친다
/// </summary>
/// <param name="_other">다른 AABB</param>
/// <returns>합쳐진 AABB</returns>
AABB AABB::Union(const AABB& _other) const
{
	// 새로운 AABB 를 만들고
	AABB tmp = AABB();

	// 각 AABB의 최소 최대를 구한다
	tmp.minPoint.x = min(minPoint.x, _other.minPoint.x);
	tmp.minPoint.y = min(minPoint.y, _other.minPoint.y);
	tmp.maxPoint.x = max(maxPoint.x, _other.maxPoint.x);
	tmp.maxPoint.y = max(maxPoint.y, _other.maxPoint.y);

	return tmp;
}

/// <summary>
/// 넓이 구하기
/// </summary>
/// <returns>넓이</returns>
float AABB::GetArea() const
{
	return ((this->maxPoint.x - this->minPoint.x) * (this->maxPoint.y - this->minPoint.y));
}

/// <summary>
/// 포함 관계인지
/// </summary>
/// <param name="_collider">다른 충돌체</param>
/// <returns>포함 여부</returns>
bool AABB::Contains(Collider* _collider) const
{
	Vector2 colliderMin = _collider->GetMinPoint();
	Vector2 colliderMax = _collider->GetMaxPoint();

	if (this->minPoint.x <= colliderMin.x && this->minPoint.y <= colliderMin.y
		&& this->maxPoint.x >= colliderMax.x && this->maxPoint.y >= colliderMax.y)
		return true;

	return false;
}

/// <summary>
/// 충돌하는지
/// </summary>
/// <param name="_other">충돌체</param>
/// <returns>충돌 여부</returns>
bool AABB::IsCollision(const AABB& _other) const
{
	if (this->minPoint.x <= _other.maxPoint.x && this->maxPoint.x >= _other.minPoint.x
		&& this->minPoint.y <= _other.maxPoint.y && this->maxPoint.y >= _other.minPoint.y)
		return true;

	return false;
}