#pragma once

#include "headers.h"
/// <summary>
/// ���� Ŭ����
/// ���� �ۼ��� : 2023/07/20
/// ���� �ۼ��� : 2023/07/25
/// �ۼ��� : ����ȯ
/// 
/// 2D ���� ������ ���� Ŭ����
/// </summary>

class Matrix;

class Vector2
{
public:
	// ������
	Vector2(int _a, int _b);
	Vector2(float _a = 0.f, float _b = 0.f);

	~Vector2();

	// ��
	float x;
	float y;

public:
	// ������ �����ε�
	Vector2 operator+(const Vector2& _other) const;

	Vector2 operator-(const Vector2& _other) const;

	Vector2 operator*(const Matrix& _vector) const;
	float operator*(const Vector2& _other) const;
	Vector2 operator*(const float& _other) const;

	Vector2 operator/(const float& _scale) const;
	Vector2 operator/(const int& _scale) const;

	void operator+=(const Vector2& _other);

	void operator-=(const Vector2& _other);

	void operator*=(const float& _other);
	void operator*=(const Matrix& _vector);

	Vector2 operator-();
	Vector2 operator-() const;

	bool operator<(const Vector2& _other) const;
	bool operator<=(const Vector2& _other) const;
	bool operator>(const Vector2& _other) const;
	bool operator>=(const Vector2& _other) const;
	bool operator==(const Vector2& _other) const;

	// ��Ʈ ������ (����)
	float Length() const;
	float Dot(const Vector2& _other) const;
	bool Normalize();

	static Vector2 Zero();
	static Vector2 One();
	static Vector2 UnitX();
	static Vector2 UnitY();

};

