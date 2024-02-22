#pragma once

#include "ClientDefines.h"
#include "ClientHeaders.h"

class Dealer;

class WhiteEffect : public Object
{
	bool isOnEff;
	Dealer* dealer;
	int dealCutSceneX;
	float op;
	float holeop;
	float time;
	float holeTime;
	Animation* animation = nullptr;
	int cutscenenum;
	bool effEnd;
	bool soundFlag;

public:
	WhiteEffect(ManagerSet* _managers);
	~WhiteEffect();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void GetDealer(Dealer* _dealer) { dealer = _dealer; }
};