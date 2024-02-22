#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// 몬스터를 얼릴 때 나오는 이펙트
/// 김정우
/// </summary>
/// 

class Monster;

class FrozEffect : public Object
{
	Animation* animation;
	Monster* monster;
	bool isOnOff;
	float elapsedTime;

public:
	FrozEffect(ManagerSet* _managers);
	~FrozEffect();

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

