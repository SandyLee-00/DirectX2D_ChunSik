#include "AABB.h"
#include "Collider.h"

AABB::AABB()
{

}

AABB::AABB(const Vector2& _minPoint, const Vector2& _maxPoint)
{

}

/// <summary>
/// �� AABB�� ��ģ��
/// </summary>
/// <param name="_other">�ٸ� AABB</param>
/// <returns>������ AABB</returns>
AABB AABB::Union(const AABB& _other) const
{
	// ���ο� AABB �� �����
	AABB tmp = AABB();

	// �� AABB�� �ּ� �ִ븦 ���Ѵ�
	tmp.minPoint.x = min(minPoint.x, _other.minPoint.x);
	tmp.minPoint.y = min(minPoint.y, _other.minPoint.y);
	tmp.maxPoint.x = max(maxPoint.x, _other.maxPoint.x);
	tmp.maxPoint.y = max(maxPoint.y, _other.maxPoint.y);

	return tmp;
}

/// <summary>
/// ���� ���ϱ�
/// </summary>
/// <returns>����</returns>
float AABB::GetArea() const
{
	return ((this->maxPoint.x - this->minPoint.x) * (this->maxPoint.y - this->minPoint.y));
}

/// <summary>
/// ���� ��������
/// </summary>
/// <param name="_collider">�ٸ� �浹ü</param>
/// <returns>���� ����</returns>
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
/// �浹�ϴ���
/// </summary>
/// <param name="_other">�浹ü</param>
/// <returns>�浹 ����</returns>
bool AABB::IsCollision(const AABB& _other) const
{
	if (this->minPoint.x <= _other.maxPoint.x && this->maxPoint.x >= _other.minPoint.x
		&& this->minPoint.y <= _other.maxPoint.y && this->maxPoint.y >= _other.minPoint.y)
		return true;

	return false;
}