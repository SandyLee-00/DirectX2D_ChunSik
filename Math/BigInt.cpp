#include "BigInt.h"
#include <iostream>

/// <summary>
/// long to BigInt
/// </summary>
/// <param name="_l">long</param>
BigInt::BigInt(long _l)
{
	// long�� ���ڿ��� �ٲ� �� �����
	std::string s = std::to_string(_l);
	Make(s);
}

/// <summary>
/// string to BigInt
/// </summary>
/// <param name="_s">string</param>
BigInt::BigInt(std::string _s)
{
	Make(_s);
}

BigInt::~BigInt()
{

}

/// <summary>
/// ���� ���� 0 ����
/// </summary>
/// <param name="a">BigInt</param>
void BigInt::Set(BigInt& a)
{
	while (a.value.size() > 1 && a.value.back() == 0)
	{
		a.value.pop_back();
	}
}

/// <summary>
/// BigInt ����
/// </summary>
/// <param name="_s">���ڿ�</param>
void BigInt::Make(std::string& _s)
{
	// �� ���ڿ��� ��� 0 ����
	if (_s.size() == 0)
	{
		this->value.push_back(0);
		return;
	}

	// �ϴ� 8�� ��� �ڸ��� �� ������ �տ� 0�� �߰�
	while (_s.size() % this->maxDigit != 0)
	{
		_s = '0' + _s;
	}

	// 8�� ��� ������ �� ���Ϳ� �ֱ�
	for (size_t i = 0; i < _s.size(); i += this->maxDigit) {
		int v = 0;
		for (size_t j = i; j < i + this->maxDigit; j++)
		{
			v = v * 10 + (_s[j] - '0');
		}
		this->value.insert(this->value.begin(), v);
	}

	// ���ʿ��� 0 ����
	Set(*this);
}

bool BigInt::operator<(BigInt _other)
{
	Set(*this);
	Set(_other);

	if (this->value.size() != _other.value.size())
	{
		return (this->value.size() < _other.value.size());
	}

	for (size_t i = this->value.size(); i > 0; i--)
	{
		if (this->value[i - 1] != _other.value[i - 1])
		{
			return (this->value[i - 1] < _other.value[i - 1]);
		}
	}
	return false;
}

bool BigInt::operator>(BigInt _other)
{
	return _other < *this;
}

bool BigInt::operator==(BigInt _other)
{
	// ����� �ٸ��� ����
	if (this->value.size() != _other.value.size())
	{
		return (this->value.size() == _other.value.size());
	}

	// ���� ��ȸ�ϸ鼭 ��
	for (size_t i = this->value.size(); i > 0; i--)
	{
		if (this->value[i - 1] != _other.value[i - 1])
		{
			return (this->value[i - 1] == _other.value[i - 1]);
		}
	}

	return true;
}

std::string BigInt::GetString()
{
	std::string s = "";
	for (size_t i = this->value.size() - 1; i > 0; i--)
	{
		s += std::to_string(this->value[i]);
		if (i != this->value.size() - 1)
		{
			for (size_t j = std::to_string(this->value[i]).length(); j < 6; j++)
			{
				s += "0";
			}
		}

	}

	s += std::to_string(this->value[0]);
	for (size_t i = std::to_string(this->value[0]).length(); i < 6; i++)
	{
		s += "0";
	}
	return s;
}

void BigInt::operator=(const BigInt& _other)
{
	this->value = _other.value;
}

BigInt BigInt::operator+(BigInt _other)
{
	// ���ʿ� 0 ����
	Set(*this);
	Set(_other);

	// �����
	BigInt ans = 0;
	ans.value.pop_back();
	// ������
	int carry = 0;

	// �� �� ū ������ ��ŭ �ݺ�
	for (size_t i = 0; i < (this->value.size() > _other.value.size() ? this->value.size() : _other.value.size()); i++)
	{
		// ��ȿ�� �ڸ������ ���� �� ���ϱ�
		if (i < this->value.size())
		{
			carry += this->value[i];
		}
		if (i < _other.value.size())
		{
			carry += _other.value[i];
		}
		// ���� ���� base�� ���� ������ �� �Է�
		ans.value.push_back(carry % this->base);
		// ������ ���ϱ�
		carry /= this->base;
	}
	// ���������� �������� �ִٸ�
	if (carry)
	{
		ans.value.push_back(carry);
	}
	// ���ʿ� 0 ����
	Set(ans);
	return ans;
}


BigInt BigInt::operator-(BigInt _other)
{
	Set(*this);
	Set(_other);
	BigInt ans;
	int carry = 0;
	for (size_t i = 0; i < this->value.size(); i++) {
		carry += this->value[i] - (i < _other.value.size() ? _other.value[i] : 0);
		if (carry < 0)
		{
			ans.value.push_back(carry + this->base), carry = -1;
		}
		else ans.value.push_back(carry), carry = 0;
	}
	Set(ans);
	return ans;
}

BigInt BigInt::operator*(BigInt _other)
{
	Set(*this);
	Set(_other);
	BigInt ans = 0;
	ans.value.assign(this->value.size() + _other.value.size(), 0);
	for (size_t i = 0; i < this->value.size(); i++) {
		unsigned long carry = 0l;
		for (size_t j = 0; j < _other.value.size() || carry > 0; j++) {
			unsigned long s = ans.value[i + j];
			s += carry;
			if (j < _other.value.size())
			{
				s += (unsigned long)this->value[i] * (unsigned long)_other.value[j];
			}
			ans.value[i + j] = s % (unsigned long)this->base;
			carry = s / (unsigned long)this->base;
		}
	}
	Set(ans);
	return ans;
}


BigInt BigInt::operator/(BigInt _other)
{
	Set(*this);
	Set(_other);

	assert(!(_other.value.size() == 0 || (_other.value.size() == 1 && _other.value[0] == 0)) && "Devied 0 in BigInt");
	BigInt ans, cur;
	for (size_t i = this->value.size(); i > 0; i--) {
		cur.value.insert(cur.value.begin(), this->value[i - 1]);
		int x = 0, L = 0, R = this->base;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (_other * BigInt(mid) > cur) {
				x = mid;
				R = mid - 1;
			}
			else
				L = mid + 1;
		}
		cur = cur - BigInt(x - 1) * _other;
		ans.value.insert(ans.value.begin(), x - 1);
	}
	Set(ans);
	return ans;
}


