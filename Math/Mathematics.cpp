#include "Mathematics.h"

/// <summary>
/// 3단외적
/// </summary>
/// <param name="_target">저장할 벡터</param>
/// <param name="_a">a 벡터</param>
/// <param name="_b">b 벡터</param>
/// <param name="_c">c 벡터</param>
void Mathematics::TripleProduct(Vector2& _target, const Vector2& _a, const Vector2& _b, const Vector2& _c)
{
	// 수학적 방식에 따른 3단 외적
	Vector2 r;

	float ac = _a.x * _c.x + _a.y * _c.y; // perform a.dot(c)
	float bc = _b.x * _c.x + _b.y * _c.y; // perform b.dot(c)

	// perform b * a.dot(c) - a * b.dot(c)
	r.x = _b.x * ac - _a.x * bc;
	r.y = _b.y * ac - _a.y * bc;

	_target = { r.x, r.y };

	return;
}

/// <summary>
/// 벡터의 길이 구하기
/// </summary>
/// <param name="_vector">벡터</param>
/// <returns>길이</returns>
float Mathematics::Lenght(const Vector2& _vector)
{
	return (float)sqrt(pow(_vector.x, 2) + pow(_vector.y, 2));
}

/// <summary>
/// 벡터의 일반화
/// </summary>
/// <param name="_vector">벡터</param>
void Mathematics::Normalize(Vector2& _vector)
{
	float lenght = Lenght(_vector);
	if (lenght == 0)
	{
		return;
	}

	_vector.x /= lenght;
	_vector.y /= lenght;
}

/// <summary>
/// 일반화 된 벡터 반환
/// 원본을 수정하지 않고 일반화 된 벡터만 반환
/// </summary>
/// <param name="_vector">원본 벡터</param>
/// <returns>일반화 된 벡터</returns>
Vector2 Mathematics::GetNormalize(const Vector2& _vector)
{
	float lenght = Lenght(_vector);
	if (lenght == 0)
	{
		return{ 0, 0 };
	}
	Vector2 result;
	result.x = _vector.x / lenght;
	result.y = _vector.y / lenght;

	return result;
}

/// <summary>
/// 주어진 벡터 3개가 시계방향인지
/// a -> b -> c 순으로
/// </summary>
/// <param name="_a">벡터 a</param>
/// <param name="_b">벡터 b</param>
/// <param name="_c">벡터 c</param>
/// <returns></returns>
bool Mathematics::IsClockWise(const Vector2& _a, const Vector2& _b, const Vector2& _c)
{
	// 외적 결과
	float result = _a.x * _b.y + _b.x * _c.y + _c.x * _a.y - (_b.x * _a.y + _c.x * _b.y + _a.x * _c.y);
	// 0 이하면 시계방향이다
	return result < 0;
}

float Mathematics::Cross(Vector2 _a, Vector2 _b)
{
	return _a.x * _b.y - _a.y * _b.x;
}

// TODO: 이해할것
bool Mathematics::LineSegementsIntersect(Vector2 _p, Vector2 _p2, Vector2 _q, Vector2 _q2, Vector2& _intersection)
{
	Vector2 r = _p2 - _p;
	Vector2 s = _q2 - _q;
	float rxs = Cross(r, s);
	float qpxr = Cross(_q - _p, r);

	if (IsZero(rxs) && IsZero(qpxr))
	{
		return false;
	}

	if (IsZero(rxs) && !IsZero(qpxr))
	{
		return false;
	}

	float t = Cross(_q - _p, s) / rxs;

	float u = Cross(_q - _p, r) / rxs;

	if (!(abs(rxs) <= 0.00001f) && (0 <= t && t <= 1) && (0 <= u && u <= 1))
	{
		_intersection = { r.x * t + _p.x, r.y * t + _p.y };

		return true;
	}

	return false;
}

