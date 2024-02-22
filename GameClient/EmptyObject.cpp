#include "EmptyObject.h"

EmptyObject::EmptyObject(ManagerSet* _managers)
	: Object("EmptyObject", _managers, OBJECT_TYPE::BACK_GROUND, (0.f, 0.f))
{

}

EmptyObject::~EmptyObject()
{

}

void EmptyObject::Start()
{

}

void EmptyObject::Update(float _deltaTime)
{

}

void EmptyObject::FinalUpdate(float _deltaTime)
{
	
}

void EmptyObject::Render(GraphicsEngine* _graphicsEngine)
{
	_graphicsEngine->DrawSprite("guarasdfasdf", 3, 0, 0, 50, 50);

}

void EmptyObject::DebugRender(GraphicsEngine* _graphicsEngine)
{
	// TODO: ������ �� ����

	// ���������� �� ������Ʈ ���� ������ֱ�
	_graphicsEngine->DrawString(0, 0, printString + "_DEBUG");

}
