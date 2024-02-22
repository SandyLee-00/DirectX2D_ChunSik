#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Dealer;
class Guardian;

class ShieldFromSupporter
	: public Object
{
private:
	Object* parent;
	bool isOnOff;

	Object* target;
	const Vector2 SHEILD_RANGE = Vector2(96.f * 3, 96.f * 3);
	Animation* dealShieldAnimation;
	Animation* guardShieldAnimation;
	
	Dealer* dealer;
	Guardian* guardian;

	Transform* dealerTransform;
	Transform* guardTransform;

public:
	ShieldFromSupporter(ManagerSet* _managers);
	~ShieldFromSupporter();
	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetParent(Object* _parent) { parent = _parent; };
	Object* GetParent() { return parent; };
	void SetTargetDealer(Dealer* _parent) { dealer = _parent; };
	Dealer* GetTargetDealer() { return dealer; };
	void SetTargetGaurdian(Guardian* _parent) { guardian = _parent; };
	Guardian* GetTargetGaurdian() { return guardian; };

	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; };
	bool GetOnOff() { return isOnOff; };

	void SetTarget(Object* _target) { target = _target; };
};

