#include "Rigidbody.h"

Rigidbody::Rigidbody(Object* _owner)
	: Component(CALL_ORDER::RIGID_BODY, "Rigidbody", _owner)
	, velocity{}
	, force{}
	, isGravity(false)
	, gravity(10.0f)
	, mass(1.0f)
	, iMass(1.0f)
{

}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::Update(float _dt)
{
}

void Rigidbody::Render(GraphicsEngine* _graphicsEngine)
{
}

void Rigidbody::ApplyForce()
{

}

void Rigidbody::SetMass(float _val)
{
	assert(_val > 0.0f && "mass can't be negative or zero");

	this->mass = _val;
	this->iMass = 1 / this->mass;
}
