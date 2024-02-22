#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Guardian;
class RangeSupporterSheild;

class ShieldToGuardian : public Object
{
	// �ǵ� ����
	const Vector2 SHIELD_RANGE = Vector2(96.f * 3, 96.f * 3);
	
	// �ǵ� ���� �ð�
	const float SHIELD_TIME = 8.0f;
	float shieldElapseTime;

	// ����� �ִϸ��̼�
	Animation* animation;

	// ����� ���
	Guardian* guardian;
	// �ǵ� �ݶ��̴��� ����
	RangeSupporterSheild* rangeSupporterShield;

	// �¿��� ��ư
	bool isOnOff;

	// �ǵ尡 ä������
	bool isFull;

public:
	ShieldToGuardian(ManagerSet* _managers);
	~ShieldToGuardian();
	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;
	Guardian* GetGuardian() const { return guardian; }
	void SetGuardian(Guardian* val) { guardian = val; }
	RangeSupporterSheild* GetRangeSupporterShield() const { return rangeSupporterShield; }
	void SetRangeSupporterShield(RangeSupporterSheild* val) { rangeSupporterShield = val; }
	bool GetOnOff() const { return isOnOff; }
	void SetOnOff(bool val) { isOnOff = val; }
};

