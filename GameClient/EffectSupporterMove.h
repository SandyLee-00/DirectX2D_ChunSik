#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

class Supporter;

class EffectSupporterMove
	: public Object
{

private:
	bool isOnOff;
	Supporter* supporter;
	Animation* animation;
	float elapsedTime;

public:
	EffectSupporterMove(ManagerSet* _managers);
	~EffectSupporterMove();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; }
	void SetSupporter(Supporter* _supporter) { supporter = _supporter; }
};

