#include "DemoScene.h"
#include "CollisionManager.h"
#include "ManagerSet.h"
#include "DemoObject.h"
#include "DrawObject.h"
#include "Scene.h"

DemoScene::DemoScene(ManagerSet* _manager)
	: Scene(_manager)
{
	this->demoPool = new ObjectPool<DemoObject, 100>(_manager);
}

DemoScene::~DemoScene()
{

}

void DemoScene::Update(float _dt)
{
	Scene::Update(_dt);
	if (this->managers->GetKeyManager()->GetKeyState(KEY::SPACE) == KEY_STATE::DOWN)
	{
	}
}

void DemoScene::Render(GraphicsEngine* _graphicsEngine)
{
	Scene::Render(_graphicsEngine);
	_graphicsEngine->DrawTextCC(0, 0, std::to_string((int)(1 / this->managers->GetTimeManager()->GetfDT())).c_str());
}

void DemoScene::Enter()
{

	DrawObject* demoObject1 = new DrawObject(this->managers);
	managers->GetSceneManager()->AddObject(demoObject1);

	DemoObject* demoobj = new DemoObject(this->managers);
	managers->GetSceneManager()->AddObject(demoobj);

	// this->managers->GetSceneManager()->GetCurrentScene()->AddObject(this->demoPool->GetObject());
}

void DemoScene::Exit()
{
}
