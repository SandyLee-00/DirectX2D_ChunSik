#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Dealer;
class RangeSupporterSheild;

class ShieldToDealer : public Object
{
private:
	bool isOnOff;

	// 실드 지속 시간
	const float SHIELD_TIME = 4.f;
	float shieldElapseTime;

	const Vector2 SHEILD_RANGE = Vector2(96.f * 3, 96.f * 3);
	Animation* animation;

	
	Dealer* dealer;
	// 실드 콜라이더와 연결
	RangeSupporterSheild* rangeSupporterShield;
	// 실드가 채워졌나
	bool isFull;


public:
	ShieldToDealer(ManagerSet* _managers);
	~ShieldToDealer();
	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;


	void SetDealer(Dealer* _parent) { dealer = _parent; };
	Dealer* GetDealer() { return dealer; }
	RangeSupporterSheild* GetRangeSupporterShield() const { return rangeSupporterShield; }
	void SetRangeSupporterShield(RangeSupporterSheild* val) { rangeSupporterShield = val; }
	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; };
	bool GetOnOff() { return isOnOff; };

};

