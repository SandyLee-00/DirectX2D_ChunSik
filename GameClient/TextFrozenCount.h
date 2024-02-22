#pragma once
#include "ClientHeaders.h"

/// <summary>
/// 이서영
/// 전체 씬에서 HOLD 상태인 몬스터를 찾아서 카운트
/// 카운트 한 값을 텍스트로 출력
/// 
/// 현재 씬에 접근해서 모든 몬스터를 찾는 부분이 마음에 안든다 
/// </summary>

class TextFrozenCount
	: public Object
{
private:
	bool isWorking;
	int HOLDMonsterCount;

public:
	TextFrozenCount(ManagerSet* _managers);
	~TextFrozenCount();

	void Start() override;
	void Update(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;

	int GetHOLDMonsterCount() const { return HOLDMonsterCount; }
	void SetHOLDMonsterCount(int val) { HOLDMonsterCount = val; }

	void PlusCount();
	void MinusCount();
};
