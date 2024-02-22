#include "TimeManager.h"
TimeManager::TimeManager()
	: currentCount{}
	, frequency{}
	, prevCount{}
	, DT(0)
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&prevCount);

	// �ʴ� ī��Ʈ Ƚ�� (õ��)
	QueryPerformanceFrequency(&frequency);
}

TimeManager::~TimeManager()
{

}

/// <summary>
/// �ð� ������Ʈ
/// </summary>
void TimeManager::Update()
{
	QueryPerformanceCounter(&currentCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	DT = (double)(currentCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;
#ifdef _DEBUG
	if (DT > 0.16) 
	{
		DT = 0.16;
	}
#endif // _DEBUG
	// ����ī��Ʈ ���� ���簪���� ���� (�������� ����� ���ؼ�)
	prevCount = currentCount;
}
