#pragma once
#include "Scene.h"
#include <vector>
#include "ObjectPool.h"
#include "DemoObject.h"

class DemoScene :
    public Scene
{
private:
    ObjectPool<DemoObject, 100>* demoPool;
    const float interval = 10.0f;

public:
    DemoScene(ManagerSet* _manager);
    ~DemoScene();

	void Update(float _dt) override;
	void Render(GraphicsEngine* _graphicsEngine) override;

    void Enter() override;
    void Exit() override;

};

