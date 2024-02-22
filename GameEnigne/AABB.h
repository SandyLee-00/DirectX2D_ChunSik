#pragma once
#include "headers.h"

class Collider;

/// <summary>
/// AABB 클래스
/// 최초 작성일 : 2023/08/07
/// 최초 작성일 : 2023/08/07
/// 작성자 : 김형환
/// 
/// AABB Tree 구현을 위한
/// 나중에 BoxCollider의 콜리젼 처리도 이걸로 바꿀 것
/// <\summry>
class AABB
{
public:
	Vector2 minPoint;
	Vector2 maxPoint;

public:
	AABB();
	AABB(const Vector2& _minPoint, const Vector2& _maxPoint);

	// 2개의 AABB를 병합
	AABB Union(const AABB& _other)const;
	// 사각형의 넓이 반환  
	float GetArea()const;
	// 콜라이더가 확장한 사각형 내부에 있는지 
	bool Contains(Collider* _collider) const;

	bool IsCollision(const AABB& _other) const;
};