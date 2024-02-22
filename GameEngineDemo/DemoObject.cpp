#include "DemoObject.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ManagerSet.h"
#include <random>
#include "BigInt.h"
#include "random.h"
#include "ParticleSystem.h"
#include "DemoParticle.h"

DemoObject::DemoObject(ManagerSet* _manager)
	: Object("Demo", _manager, OBJECT_TYPE::PLAYER, { 100, 100 })
	, movable(false)
	, demoint(1)
{

}

DemoObject::~DemoObject()
{

}

void DemoObject::Start()
{
	// OutputDebugString(L"Object Start\n");
	CreateComponent<BoxCollider>();
	this->GetManagers()->GetCollisionManager()->AddCollider(GetComponent<BoxCollider>());
	ResourceManager* rm = this->GetManagers()->GetResourceManager();
	PathManager* pm = this->GetManagers()->GetPathManager();


	GetComponent<Transform>()->SetPosition(random::GetRandom({0, 0}, {500, 500}));
	rm->LoadImage("test", pm->GetResourcePath(L"Example\\cha_2nd.jpg"));

	CreateComponent<ParticleSystem<DemoParticle>>();
}


void DemoObject::Update(float _deltaTime)
{
	TimeManager* tm = this->GetManagers()->GetTimeManager();
	KeyManager* km = this->GetManagers()->GetKeyManager();
	Transform* tranform = this->GetComponent<Transform>();

	if (movable)
	{
		float movement = tm->GetfDT();

		if (km->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
		{
			tranform->Translation({ -100 * _deltaTime, 0.0f });
		}

		if (km->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
		{
			tranform->Translation({ 0.0f, -100 * _deltaTime });
		}

		if (km->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
		{
			tranform->Translation({ 100 * _deltaTime, 0.0f });
		}

		if (km->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
		{
			tranform->Translation({ 0.0f, 100 * _deltaTime });
		}

	}
	if (km->GetKeyState(KEY::SPACE) == KEY_STATE::DOWN)
	{
		// SetState(OBJECT_STATE::DEAD);
		// GetComponent<ParticleSystem<DemoParticle>>()->GenerateParticle();
		BigInt icescore = 1;
		BigInt icebase = 1024;
		for (int i = 0; i < 30 - 5; i++)
		{
			icescore *= 2;
		}
 		icescore *= icebase;
		this->demoint += icescore;
	}
}

void DemoObject::FinalUpdate(float _deltaTime)
{
}

void DemoObject::Render(GraphicsEngine* _graphicsEngine)
{
	Matrix temp = GetComponent<Transform>()->GetTransformationMatrix();
	_graphicsEngine->DrawEmptyRect((int)temp[3][0], (int)temp[3][1], (int)temp[3][0] + 100, (int)temp[3][1] + 100);
	_graphicsEngine->DrawString(100, 100, this->demoint.GetString());
// 	int a = this->GetManagers()->GetResourceManager()->GetImageId("test");
// 	_graphicsEngine->DrawSprite(
// 		"test",
// 		a,
// 		(int)temp[3][0],
// 		(int)temp[3][1],
// 		600,
// 		600
// 	);
// 	BigInt bi(1);
// 
// 	for (int i = 0; i < 100; i++)
// 	{
// 		bi *= 2;
// 	}

	// _graphicsEngine->DrawTextCC(100, 100, bi.GetString().c_str());
}

void DemoObject::DebugRender(GraphicsEngine* _graphicsEngine)
{
	//ComponentRender(_graphicsEngine);
}

//void DemoObject::OnCollisionEnter(const Object* _other)
//{
//// 	OutputDebugString(L"Collision Enter");
//// 	OutputDebugStringA(this->GetName().c_str());
//// 	OutputDebugString(L"\n");
//}
//
//void DemoObject::OnCollisionStay(const Object* _other)
//{
//}
//
//void DemoObject::OnCollisionExit(const Object* _other)
//{
//// 	OutputDebugString(L"Collision Exit");
//// 	OutputDebugStringA(this->GetName().c_str());
//// 	OutputDebugString(L"\n");
//}
