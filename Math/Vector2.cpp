#include "Vector2.h"
#include "Mathematics.h"
#include "Matrix.h"

Vector2::Vector2(float _a /*= 0*/, float _b /*= 0*/)
	: x(_a)
	, y(_b)
{
}

Vector2::Vector2(int _a, int _b)
	: x((float)_a)
	, y((float)_b)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(const Vector2& _other) const
{
	return { this->x + _other.x, this->y + _other.y };
}

void Vector2::operator+=(const Vector2& _other)
{
	this->x += _other.x;
	this->y += _other.y;
}

void Vector2::operator*=(const Matrix& _vector)
{
	(*this) = (*this) * _vector;
}


Vector2 Vector2::operator/(const float& _scale) const
{
	const float RScale = 1.f / _scale;
	return Vector2(x * RScale, y * RScale);
}

Vector2 Vector2::operator/(const int& _scale) const
{
	const float RScale = 1.f / (float)_scale;
	return Vector2(x * RScale, y * RScale);
}

Vector2 Vector2::operator-(const Vector2& _other) const
{
	return { this->x - _other.x, this->y - _other.y };
}

void Vector2::operator-=(const Vector2& _other)
{
	this->x -= _other.x;
	this->y -= _other.y;
}

Vector2 Vector2::operator-()
{
	return { -this->x, -this->y };
}

Vector2 Vector2::operator-() const
{
	return { -this->x, -this->y };
}

bool Vector2::operator<(const Vector2& _other) const
{
	return (this->x < _other.x && this->y < _other.y);
}

bool Vector2::operator<=(const Vector2& _other) const
{
	return (this->x <= _other.x && this->y <= _other.y);
}

bool Vector2::operator>(const Vector2& _other) const
{
	return (this->x > _other.x && this->y > _other.y);
}

bool Vector2::operator>=(const Vector2& _other) const
{
	return (this->x >= _other.x && this->y >= _other.y);
}

float Vector2::operator*(const Vector2& _other) const
{
	return (this->x * _other.x + this->y * _other.y);
}

Vector2 Vector2::operator*(const float& _other) const
{
	return { this->x * _other, this->y * _other };
}

void Vector2::operator*=(const float& _other)
{
	this->x *= _other;
	this->y *= _other;
}

Vector2 Vector2::operator*(const Matrix& _matrix) const
{
	return _matrix * (*this);
}

bool Vector2::operator==(const Vector2& _other) const
{
	return (this->x == _other.x && this->y == _other.y);
}

/// <summary>
/// 벡터의 길이
/// </summary>
/// <returns>길이</returns>
float Vector2::Length() const
{
	return sqrtf(this->x * this->x + this->y * this->y);
}

/// <summary>
/// 내적
/// </summary>
/// <param name="_other">내적 할 벡터</param>
/// <returns>내적 값</returns>
float Vector2::Dot(const Vector2& _other) const
{
	return (this->x * _other.x + this->y * _other.y);
}

/// <summary>
/// 일반화
/// </summary>
/// <returns>일반화 성공 여부</returns>
bool Vector2::Normalize()
{
	const float SquareSum = x * x + y * y;
	const float Tolerance = 1.e-8f;
	if (SquareSum > Tolerance)
	{
		const float Scale = 1.f / sqrtf(SquareSum);
		x *= Scale;
		y *= Scale;
		return true;
	}
	x = 0.f;
	y = 0.f;
	return false;
}

/// <summary>
/// 0벡터 생성
/// </summary>
/// <returns>0벡터</returns>
Vector2 Vector2::Zero()
{
	return Vector2(0.f, 0.f);
}

/// <summary>
/// 1벡터 생성
/// </summary>
/// <returns>1벡터</returns>
Vector2 Vector2::One()
{
	return Vector2(1.f, 1.f);
}

/// <summary>
/// x 단위벡터
/// </summary>
/// <returns>x 단위벡터</returns>
Vector2 Vector2::UnitX()
{
	return Vector2(1.f, 0.f);
}

/// <summary>
/// y 단위벡터
/// </summary>
/// <returns>y 단위벡터</returns>
Vector2 Vector2::UnitY()
{
	return Vector2(0.f, 1.f);
}
