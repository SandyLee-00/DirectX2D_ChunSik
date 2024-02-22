#pragma once
#include "headers.h"
/// <summry>
/// 시간 매니저
/// 최초 작성일 : 2023/07/21
/// 최초 작성일 : 2023/07/27
/// 작성자 : 김형환
/// 
/// 시간 컨트롤 및 프레임 제어를 위한 매니저
/// <\summry>
class TimeManager
{
private:
	LARGE_INTEGER currentCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER frequency;

	double DT;

public:
	TimeManager();
	~TimeManager();

public:
	void Initalize() {};

	void Update();

	double GetDT() { return DT; }
	float GetfDT() { return (float)DT; }
};