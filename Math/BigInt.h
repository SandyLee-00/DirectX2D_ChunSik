#pragma once
#include "headers.h"

/// <summary>
/// BigInt Ŭ����
/// 
/// ���� �ۼ��� : 2023/08/07
/// ���� �ۼ��� : 2023/08/09
/// �ۼ��� : ����ȯ
/// 
/// 32 ��Ʈ���� ū ������ �ٷ�� ���� Ŭ����
/// ��ȣ �ʿ� ����
/// <\summry>

// �̷л� 96��Ʈ �������� ����
// ��ȣ ����
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

