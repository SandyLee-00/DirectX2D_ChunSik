#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Guardian;

class RangeGuardianAttack
	: public Object
{
private:
	// -----------------------------------
	// 밸런스 시트 const 값들

	// 가디언 공격 범위
	const Vector2 ATTACK_RANGE = Vector2(96.f * 3, 96.f);

	// 가디언 공격 쿨타임
	const float ATTACK_COOLTIME = 3.0f;

	// 가디언 공격 시간
	const float ATTACKTIME = 1.0f;

	// 밸런스 시트 const 값들
	// -----------------------------------

	Object* parent;
	bool isOnOff;
	float elapsedTime;

	
public:
	RangeGuardianAttack(ManagerSet* _managers);
	~RangeGuardianAttack();

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

	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; };
	bool GetOnOff() { return isOnOff; };

};

