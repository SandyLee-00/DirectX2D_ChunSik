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
	// TODO: 검정색 펜 쓰기

	// 디버깅용으로 빈 오브젝트 글자 출력해주기
	_graphicsEngine->DrawString(0, 0, printString + "_DEBUG");

}
