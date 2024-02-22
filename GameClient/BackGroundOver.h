#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// 
/// UI�� ���� ���̾��� ��� �׸��� ���� ��
/// ���� ���� �� �������� �ϱ� / HP�� �ؿ� ȸ�� �ڽ� �׸��� ��
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

