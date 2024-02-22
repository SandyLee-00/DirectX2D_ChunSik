#include "Panel.h"

Panel::Panel(ManagerSet* _manager)
	:Object("Panel", _manager, OBJECT_TYPE::UI, { 200, 200})
{

}

Panel::~Panel()
{

}

void Panel::Start()
{

}

void Panel::Update(float _deltaTime)
{

}

void Panel::FinalUpdate(float _deltaTime)
{
	ComponentUpdate(_deltaTime);
}

void Panel::Render(GraphicsEngine* _graphicsEngine)
{

}

void Panel::DebugRender(GraphicsEngine* _graphicsEngine)
{

}
