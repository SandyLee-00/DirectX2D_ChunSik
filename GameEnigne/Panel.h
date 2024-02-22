#pragma once
#include "Object.h"
#include "Vector2.h"

class Panel
	: public Object
{
protected:
	// 	Sprite* sourceImage;

public:
	Panel(ManagerSet* _manager);
	~Panel();
	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void FinalUpdate(float _deltaTime) override;
	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;
};

