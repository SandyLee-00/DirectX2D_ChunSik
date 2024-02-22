#pragma once
#include "ClientHeaders.h"
//#include "BigInt.h"

/// <summary>
/// ������
/// ��ŷ ���� ���� ������ Ŭ����
/// </summary>
class TextPersonData
{
	// ���� ����
	UINT64 score = 0;
	// �̸� ���� ��� -> �ð� ������ �ѱ۵�?
	std::string name{};
	// �÷��� Ÿ��
	float totalSec = 0.f;

public:
	TextPersonData(UINT64 _score, std::string _name, float _totalSec);
	TextPersonData();
	~TextPersonData();


	//-----------------------
	// Getter Setter
	UINT64 GetScore() const { return score; }
	void SetScore(UINT64 val) { score = val; }
	std::string GetName() const { return name; }
	void SetName(std::string val) { name = val; }
	float GetTotalSec() const { return totalSec; }
	void SetTotalSec(float val) { totalSec = val; }
	//-------------------------

	bool operator==(const TextPersonData& _other);
};

