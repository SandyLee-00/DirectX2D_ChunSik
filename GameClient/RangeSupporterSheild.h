#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// 서포터가 실드 키를 누르면 
/// 범위 안의 딜러 / 가디언에게 실드 isOnOff를 true로 바꿔준다.
/// </summary>

class Supporter;
class ShieldToDealer;
class ShieldToGuardian;

class RangeSupporterSheild
	: public Object
{
private:
	// -----------------------------------
	// 밸런스 시트 const 값들

	// 서포터 실드 범위
	const Vector2 SHEILD_RANGE = Vector2(96.f * 3, 96.f * 3);

	// 서포터 실드 쿨타임

	// 밸런스 시트 const 값들
	// -----------------------------------

	Supporter* supporter;

	bool isOnOff;
	ShieldToDealer* shieldToDealer;
	ShieldToGuardian* shieldToGuardian;
	Animation* animation = nullptr;
	bool soundFlag;

public:
	RangeSupporterSheild(ManagerSet* _managers);
	~RangeSupporterSheild();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetParent(Supporter* _parent) { supporter = _parent; };
	Supporter* GetParent() { return supporter; };

	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; };
	bool GetOnOff() { return isOnOff; };
	ShieldToDealer* GetShieldToDealer() const { return shieldToDealer; }
	void SetShieldToDealer(ShieldToDealer* val) { shieldToDealer = val; }
	ShieldToGuardian* GetShieldToGuardian() const { return shieldToGuardian; }
	void SetShieldToGuardian(ShieldToGuardian* val) { shieldToGuardian = val; }
};

