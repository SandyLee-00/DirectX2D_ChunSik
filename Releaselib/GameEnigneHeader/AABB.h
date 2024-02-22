#pragma once
#include "headers.h"

class Collider;

/// <summary>
/// AABB Ŭ����
/// ���� �ۼ��� : 2023/08/07
/// ���� �ۼ��� : 2023/08/07
/// �ۼ��� : ����ȯ
/// 
/// AABB Tree ������ ����
/// ���߿� BoxCollider�� �ݸ��� ó���� �̰ɷ� �ٲ� ��
/// <\summry>
class AABB
{
public:
	Vector2 minPoint;
	Vector2 maxPoint;

public:
	AABB();
	AABB(const Vector2& _minPoint, const Vector2& _maxPoint);

	// 2���� AABB�� ����
	AABB Union(const AABB& _other)const;
	// �簢���� ���� ��ȯ  
	float GetArea()const;
	// �ݶ��̴��� Ȯ���� �簢�� ���ο� �ִ��� 
	bool Contains(Collider* _collider) const;

	bool IsCollision(const AABB& _other) const;
};