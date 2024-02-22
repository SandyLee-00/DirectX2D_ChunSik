#pragma once
#include "headers.h"
#include "Component.h"
#include "GraphicsEngine.h"
#include "Collider.h"
#include "BoxCollider.h"
/// <summary>
/// ������Ʈ Ŭ����
/// ���� �ۼ��� : 2023/07/21
/// ���� �ۼ��� : 2023/08/01
/// �ۼ��� : ����ȯ
/// 
/// ��� ������Ʈ�� �θ� Ŭ����
/// 
/// �ݵ��!!!!
/// ��� ���� ������Ʈ�� �ݵ�� �� Ŭ������ ��� ���� ��!!!
/// �ݵ��!!!!
/// </summary>

class Collision;
class Transform;
class Rigidbody;
class Component;
class ManagerSet;
class Collider;
class BoxCollider;
class CircleCollider;
class ManagerSet;
class MouseEvent;

class Object abstract
{
private:
	std::string name;
	std::multimap<CALL_ORDER, Component*> components;
	bool isActivate;
	ManagerSet* managers;
	OBJECT_TYPE type;
	OBJECT_STATE state;
	bool canPause;

public:
	// ������ �Ҹ���
	Object(std::string _name, ManagerSet* _managers, OBJECT_TYPE _type, Vector2 _where = { 0,0 });
	virtual ~Object();

	// ������Ʈ �⺻ ���
	// ������Ʈ ������
	virtual void Start() {};

	// �Ҹ� ��
	void DestroyAllComponent();
	virtual void Finalize() {};

	// ������Ʈ
	virtual void Update(float _deltaTime) {};
	virtual void FinalUpdate(float _deltaTime) {};

	// ����
	virtual void Render(GraphicsEngine* graphicsEngine) {};
	virtual void DebugRender(GraphicsEngine* graphicsEngine) {};

	// �浹 ������
	virtual void OnCollisionEnter(Object* _other) {};
	virtual void OnCollisionStay(Object* _other) {};
	virtual void OnCollisionExit(Object* _other) {};

	OBJECT_TYPE GetType() const { return type; }
	void SetType(OBJECT_TYPE val) { type = val;}

	void ComponentUpdate(float _dt = 0);
	void ComponentRender(GraphicsEngine* _graphicsEngine);
	void ComponentDebugRender(GraphicsEngine* _graphicsEngine);

	bool IsAlive() { return this->GetState() != OBJECT_STATE::DEAD; }

	void Destroy();

	// ������Ʈ getter creater
	template <typename T>
	T* CreateComponent();
	template <typename T>
	T* GetComponent();

	ManagerSet* GetManagers() const { return managers; }
	std::string GetName() const { return name; }
	void SetName(std::string val) { name = val; }

	OBJECT_STATE GetState() const { return state; }
	void SetState(OBJECT_STATE val) { state = val; }
	bool GetCanPause() const { return canPause; }
	void SetCanPause(bool val) { canPause = val; }
};

template <typename T>
T* Object::CreateComponent()
{
	if (GetComponent<T>() != nullptr)
	{
		return GetComponent<T>();
	}

	T* temp = new T(this);

	Component* component = dynamic_cast<Component*>(temp);

	if (component == nullptr)
	{
		delete temp;
		return nullptr;
	}

	component->SetOwener(this);
	this->components.insert({ component->GetCallOrder(), component });

	return temp;
}

template <typename T>
T* Object::GetComponent()
{
	for (auto& component : this->components)
	{
		T* temp = dynamic_cast<T*>(component.second);

		if (temp == nullptr)
		{
			continue;
		}

		return temp;
	}

	return nullptr;
}
