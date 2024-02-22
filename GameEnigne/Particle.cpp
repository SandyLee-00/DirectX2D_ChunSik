#include "Particle.h"

Particle::Particle(ManagerSet* _managers)
	: Object("Particle", _managers, OBJECT_TYPE::EEFECT)
{

}

Particle::~Particle()
{

}

void Particle::Update(float _dt /*= 0*/)
{
}


void Particle::Render(GraphicsEngine* _graphicsEngine)
{
}

void Particle::DebugRender(GraphicsEngine* _graphicsEngine)
{
}
