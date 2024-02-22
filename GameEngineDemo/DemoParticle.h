#pragma once
#include "headers.h"
#include "Particle.h"


class DemoParticle :
    public Particle
{
private:
    Vector2 size;
    float lifetime;
    float age;
	Vector2 direction;
	float speed;
	std::string imageName;
    int imageId;

public:
    DemoParticle(ManagerSet* _managers);
    ~DemoParticle();

    void Start() override;
    void Update(float _deltaTime) override;
    void FinalUpdate(float _deltaTime) override;
    void Render(GraphicsEngine* graphicsEngine) override;
    void DebugRender(GraphicsEngine* graphicsEngine) override;

};

