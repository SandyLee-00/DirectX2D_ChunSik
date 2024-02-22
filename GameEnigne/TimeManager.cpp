#include "TimeManager.h"
TimeManager::TimeManager()
	: currentCount{}
	, frequency{}
	, prevCount{}
	, DT(0)
{
	// 현재 카운트
	QueryPerformanceCounter(&prevCount);

	// 초당 카운트 횟수 (천만)
	QueryPerformanceFrequency(&frequency);
}

TimeManager::~TimeManager()
{

}

/// <summary>
/// 시간 업데이트
/// </summary>
void TimeManager::Update()
{
	QueryPerformanceCounter(&currentCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	DT = (double)(currentCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;
#ifdef _DEBUG
	if (DT > 0.16) 
	{
		DT = 0.16;
	}
#endif // _DEBUG
	// 이전카운트 값을 현재값으로 갱신 (다음번에 계산을 위해서)
	prevCount = currentCount;
}
