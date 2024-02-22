#include "DrawObject.h"
#include "Animation.h"
#include "ManagerSet.h"
//#include "Animator.h"
DrawObject::DrawObject(ManagerSet* _manager) : Object("Demo", 
	_manager, OBJECT_TYPE::PLAYER,
	{ 100, 100 })
{
}

DrawObject::~DrawObject()
{
}

void DrawObject::Start()
{
	ResourceManager* rm = this->GetManagers()->GetResourceManager();
	PathManager* pm = this->GetManagers()->GetPathManager();

	rm->LoadImage("test", pm->GetResourcePath(L"character\\Sup_idle_ani.png"));
	rm->LoadImage("test2", pm->GetResourcePath(L"character\\Sup_move_ani.png"));
	CreateComponent<Animation>();
	temp = GetComponent<Animation>();
	//temp->Stop();
	temp->SetSpriteRes(1, L"Animation\\Sup\\SupMove.txt", "A", 0, 0);
}

void DrawObject::Update(float _deltaTime)
{

}

void DrawObject::FinalUpdate(float _deltaTime)
{
}

void DrawObject::Render(GraphicsEngine* _graphicsEngine)
{
	temp->SetSpriteRes(0, L"Animation\\Sup\\SupIdle.txt", "A", 0, 0);
	// temp->SetSpriteRes(1, L"Animation\\Sup\\SupMove.txt", "A", 0, 0);
}

void DrawObject::DebugRender(GraphicsEngine* _graphicsEngine)
{
}
