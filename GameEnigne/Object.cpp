#include "Object.h"
#include "Transform.h"
#include "MouseEvent.h"

Object::Object(std::string _name, ManagerSet* _managers, OBJECT_TYPE _type, Vector2 _where)
	: name(_name)
	, managers(_managers)
	, type(_type)
	, canPause(false)
{
	/// 모든 오브젝트는 반드시 Transform 컴포넌트가 있어야한다
	/// 절대 이부분은 수정하지 말 것
	CreateComponent<Transform>();
	GetComponent<Transform>()->SetPosition(_where);
}

Object::~Object()
{
	DestroyAllComponent();
}

/// <summary>
/// 할당된 컴포넌트 해제
/// </summary>
void Object::DestroyAllComponent()
{
	for(auto& component : this->components) 
	{
		delete component.second;
	}
}

/// <summary>
/// 컴포넌트 업데이트
/// </summary>
/// <param name="_dt">dt</param>
void Object::ComponentUpdate(float _dt)
{
	for(auto& component : this->components) 
	{
		component.second->Update(_dt);
	}
}

/// <summary>
/// 컴포넌트 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void Object::ComponentRender(GraphicsEngine* _graphicsEngine)
{
	for (auto& component : this->components)
	{
		component.second->Render(_graphicsEngine);
	}
}

void Object::ComponentDebugRender(GraphicsEngine* _graphicsEngine)
{
	for (auto& component : this->components)
	{
		component.second->DebugRender(_graphicsEngine);
	}
}

void Object::Destroy()
{
	Finalize();
}
