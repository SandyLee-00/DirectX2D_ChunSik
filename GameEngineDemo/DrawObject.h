#pragma once
#include "Object.h"

class Animator;
class Animation;

class DrawObject : public Object
{
	Animation* temp;
public:
	DrawObject(ManagerSet* _manager);
	~DrawObject();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;
};

