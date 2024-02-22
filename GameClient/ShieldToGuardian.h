#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Guardian;
class RangeSupporterSheild;

class ShieldToGuardian : public Object
{
	// 실드 범위
	const Vector2 SHIELD_RANGE = Vector2(96.f * 3, 96.f * 3);
	
	// 실드 지속 시간
	const float SHIELD_TIME = 8.0f;
	float shieldElapseTime;

	// 재생할 애니메이션
	Animation* animation;

	// 가디언 대상
	Guardian* guardian;
	// 실드 콜라이더와 연결
	RangeSupporterSheild* rangeSupporterShield;

	// 온오프 버튼
	bool isOnOff;

	// 실드가 채워졌나
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

