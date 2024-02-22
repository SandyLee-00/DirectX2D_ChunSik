#pragma once
#include "headers.h"

class Object;
class GraphicsEngine;

/// <summry>
/// Component �θ� Ŭ����
/// ���� �ۼ��� : 2023/07/23
/// ���� �ۼ��� : 2023/07/23
/// �ۼ��� : ����ȯ
/// 
/// ��� ������Ʈ�� �θ� Ŭ����
/// <\summry>

class Component
{
private:
	Object* owner;
	CALL_ORDER callOrder;
	std::string name;

public:
	Component(CALL_ORDER _order, std::string _name, Object* owner);
	virtual ~Component();

	virtual void Update(float _dt = 0) abstract;
	virtual void LateUpdate() abstract;
	virtual void Render(GraphicsEngine* _graphicsEngine) abstract;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) abstract;

	Object* GetOwner() const { return owner; }
	void SetOwener(Object* val) { owner = val; }

	CALL_ORDER GetCallOrder() const { return callOrder; }
	void SetCallOrder(CALL_ORDER val) { callOrder = val; }
};

