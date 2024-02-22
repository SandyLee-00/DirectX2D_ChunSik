#include "Object.h"
#include "Transform.h"
#include "MouseEvent.h"

Object::Object(std::string _name, ManagerSet* _managers, OBJECT_TYPE _type, Vector2 _where)
	: name(_name)
	, managers(_managers)
	, type(_type)
	, canPause(false)
{
	/// ��� ������Ʈ�� �ݵ�� Transform ������Ʈ�� �־���Ѵ�
	/// ���� �̺κ��� �������� �� ��
	CreateComponent<Transform>();
	GetComponent<Transform>()->SetPosition(_where);
}

Object::~Object()
{
	DestroyAllComponent();
}

/// <summary>
/// �Ҵ�� ������Ʈ ����
/// </summary>
void Object::DestroyAllComponent()
{
	for(auto& component : this->components) 
	{
		delete component.second;
	}
}

/// <summary>
/// ������Ʈ ������Ʈ
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
/// ������Ʈ ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
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
