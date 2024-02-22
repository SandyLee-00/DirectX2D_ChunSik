#pragma once
#include <random>
#include "Vector2.h"
namespace random
{
	template<typename T>
	T GetRandom(T _min, T _max);

	Vector2 GetRandom(const Vector2& _min, const Vector2& _max);
}	

template<typename T>
T random::GetRandom(T _min, T _max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<T> dis(_min, _max);

	return dis(gen);
}	