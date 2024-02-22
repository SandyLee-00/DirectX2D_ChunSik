#pragma once

/// <summary>

/// </summary>


#include "headers.h"
#include "Vector2.h"
#include "Matrix.h"
namespace Mathematics
{
	// 사각형 꼭지점 좌표 변환
	void TransformRectangleVertices(Vector2 _rect[4], const Matrix& _target);
	void TransformVertices(Vector2& _point, const Matrix& _target);

	// 스칼라 내적
	float DotProduct(const Vector2& _a, const Vector2& _b);

	// 벡터에 수직인 벡터
	void TripleProduct(Vector2& _target, const Vector2& _a, const Vector2& _b, const Vector2& _c);

	// 벡터의 길이
	float Lenght(const Vector2& _vector);
	void Normalize(Vector2& _vector);
	Vector2 GetNormalize(const Vector2& _vector);

	// 점 3개가 이루는 각이 시계방향인지 아닌지
	bool IsClockWise(const Vector2& _a, const Vector2& _center, const Vector2& _b);

	// 두 벡터가 겹처있는지
	bool LineSegementsIntersect(Vector2 _p, Vector2 _p2, Vector2 _q, Vector2 _q2,
		Vector2& _intersection);

	// 길이가 2인 벡터의 외적
	float Cross(Vector2 _a, Vector2 _b);

	template<typename T>
	bool IsZero(T _val) { return abs(_val) <= 0.00001; }
};
