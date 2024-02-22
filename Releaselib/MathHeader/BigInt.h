#pragma once
#include "headers.h"

/// <summary>
/// BigInt 클래스
/// 
/// 최초 작성일 : 2023/08/07
/// 최초 작성일 : 2023/08/09
/// 작성자 : 김형환
/// 
/// 32 비트보다 큰 정수를 다루기 위한 클래스
/// 부호 필요 없음
/// <\summry>

// 이론상 96비트 정수까지 가능
// 부호 없음
class BigInt
{
private:
	std::vector<int> value;
	const int base = 1'000'000;
	const int maxDigit = 6;

	void Set(BigInt& a);
	void Make(std::string& _s);

public:
	BigInt(long _l = 0);
	BigInt(std::string _s);

	~BigInt();

	void operator= (const BigInt& _other);

	BigInt operator+ (BigInt _other);
	BigInt operator- (BigInt _other);
	BigInt operator* (BigInt _other);
	BigInt operator/ (BigInt _other);

	void operator+= (BigInt _other) { *this = *this + _other; }
	void operator-= (BigInt _other) { *this = *this - _other; }
	void operator*= (BigInt _other) { *this = *this * _other; }
	void operator/= (BigInt _other) { *this = *this / _other; }

	bool operator< (BigInt _other);
	bool operator> (BigInt _other);
	bool operator==(BigInt _other);

	friend std::ostream& operator << (std::ostream& _os, const BigInt _bigInt)
	{
		std::string s = "";
		for (size_t i = 0; i < _bigInt.value.size(); i++)
		{
			s += std::to_string(_bigInt.value[i]);
		}
		_os << s;

		return _os;
	}

	std::string GetString();
};

