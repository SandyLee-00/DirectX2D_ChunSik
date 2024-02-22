#pragma once
#include "Object.h"
class Particle :
    public Object
{
protected:
    int imageId;

public:
    Particle(ManagerSet* _managers);
    virtual ~Particle();

    void Update(float _dt = 0) override;
    void Render(GraphicsEngine* _graphicsEngine) override;
    void DebugRender(GraphicsEngine* _graphicsEngine) override;
};

