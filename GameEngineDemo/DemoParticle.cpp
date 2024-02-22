#include "DemoParticle.h"
#include "random.h"
#include "ManagerSet.h"
#include "Transform.h"

DemoParticle::DemoParticle(ManagerSet* _managers)
	: Particle(_managers)
	, age(0)
	, imageName{}
	, imageId(0)
	, lifetime(0)
	, speed(0)
{
}

DemoParticle::~DemoParticle()
{

}

void DemoParticle::Start()
{
	this->size = { 50, 50 };
	this->lifetime = 0.3f;
	this->age = 0;
	this->direction = random::GetRandom({ -100, -100 }, { 100, 100 });
	this->direction.Normalize();
	this->speed = 500.0f;
	this->imageName = "testParticle";
	this->SetState(OBJECT_STATE::LIVE);
	auto pathmanager = this->GetManagers()->GetPathManager();
	auto resourceManger = this->GetManagers()->GetResourceManager();

	resourceManger->LoadImage(imageName, pathmanager->GetResourcePath(L"Example\\Effect1.png"));
	this->imageId = resourceManger->GetImageId(this->imageName);
}

void DemoParticle::Update(float _deltaTime)
{
	this->GetComponent<Transform>()->Translation(this->direction * _deltaTime * speed);
	this->age += _deltaTime;
	if (this->age >= this->lifetime) 
	{
		this->SetState(OBJECT_STATE::DEAD);
	}
}

void DemoParticle::FinalUpdate(float _deltaTime)
{
}

void DemoParticle::Render(GraphicsEngine* graphicsEngine)
{
	auto temp = this->GetComponent<Transform>()->GetTransformationMatrix();
	graphicsEngine->DrawSprite(
		this->imageName, 
		this->imageId,
		(int)temp[3][0] + 25,
		(int)temp[3][1] + 25,
		(int)this->size.x,
		(int)this->size.y
	);
}

void DemoParticle::DebugRender(GraphicsEngine* graphicsEngine)
{
}
