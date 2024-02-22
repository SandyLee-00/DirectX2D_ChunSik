#pragma once
#include "headers.h"
/// <summry>
/// �ð� �Ŵ���
/// ���� �ۼ��� : 2023/07/21
/// ���� �ۼ��� : 2023/07/27
/// �ۼ��� : ����ȯ
/// 
/// �ð� ��Ʈ�� �� ������ ��� ���� �Ŵ���
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