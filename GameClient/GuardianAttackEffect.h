#pragma once

#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// 가디언 공격 이펙트
/// 김정우
/// </summary>
/// 

class Monster;

class GuardianAttackEffect : public Object
{
	Animation* animation;
	Monster* monster;
	bool isOnOff;
	float elapsedTime;
	bool soundFlag;

public:
	GuardianAttackEffect(ManagerSet* _managers);
	~GuardianAttackEffect();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;
	bool GetOnOff() const { return isOnOff; }
	void SetOnOff(bool val) { isOnOff = val; }
	void SetMonster(Monster* val) { monster = val; }

};

