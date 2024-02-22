#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

class Monster;

class EffectFireBall
	: public Object
{
	// -----------------------------------
	// 밸런스 시트 const 값들

	const float FIREBALL_EFFECTIME = 1.0f;

	// 밸런스 시트 const 값들
	// -----------------------------------

private:
	bool isOn;
	float elapsedTime;

	Monster* monster;
	Animation* animation;

public:
	EffectFireBall(ManagerSet* _managers);
	~EffectFireBall();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetScoreOn(bool _isOn) { isOn = _isOn; }
	void SetMonster(Monster* _monster) { monster = _monster; }

};

