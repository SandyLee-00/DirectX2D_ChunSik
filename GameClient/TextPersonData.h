#pragma once
#include "ClientHeaders.h"
//#include "BigInt.h"

/// <summary>
/// 김정우
/// 랭킹 씬에 나올 데이터 클래스
/// </summary>
class TextPersonData
{
	// 최종 점수
	UINT64 score = 0;
	// 이름 현재 영어만 -> 시간 남으면 한글도?
	std::string name{};
	// 플레이 타임
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

