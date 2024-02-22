#pragma once

/// <summary>

/// </summary>


#include "headers.h"
#include "Vector2.h"
#include "Matrix.h"
namespace Mathematics
{
	// �簢�� ������ ��ǥ ��ȯ
	void TransformRectangleVertices(Vector2 _rect[4], const Matrix& _target);
	void TransformVertices(Vector2& _point, const Matrix& _target);

	// ��Į�� ����
	float DotProduct(const Vector2& _a, const Vector2& _b);

	// ���Ϳ� ������ ����
	void TripleProduct(Vector2& _target, const Vector2& _a, const Vector2& _b, const Vector2& _c);

	// ������ ����
	float Lenght(const Vector2& _vector);
	void Normalize(Vector2& _vector);
	Vector2 GetNormalize(const Vector2& _vector);

	// �� 3���� �̷�� ���� �ð�������� �ƴ���
	bool IsClockWise(const Vector2& _a, const Vector2& _center, const Vector2& _b);

	// �� ���Ͱ� ��ó�ִ���
	bool LineSegementsIntersect(Vector2 _p, Vector2 _p2, Vector2 _q, Vector2 _q2,
		Vector2& _intersection);

	// ���̰� 2�� ������ ����
	float Cross(Vector2 _a, Vector2 _b);

	template<typename T>
	bool IsZero(T _val) { return abs(_val) <= 0.00001; }
};
