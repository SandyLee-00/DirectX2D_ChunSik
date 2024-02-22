#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// 
/// UI와 같은 레이어인 배경 그리기 위한 것
/// 몬스터 나올 때 가려지게 하기 / HP바 밑에 회색 박스 그리기 등
/// </summary>

class Guardian;
class Supporter;
class Dealer;

class BackGroundOver
	: public Object
{
	Guardian* guardian;
	Supporter* supporter;
	Dealer* dealer;

	int shieldGuardianCoolTimeBarValue;
	int shieldSupporterCoolTimeBarValue;

public:
	BackGroundOver(ManagerSet* _managers);
	virtual ~BackGroundOver();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void FinalUpdate(float _deltaTime) override;
	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetGuardian(Guardian* _guardian) { guardian = _guardian; }

};

