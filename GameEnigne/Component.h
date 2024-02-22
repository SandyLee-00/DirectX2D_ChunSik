#pragma once
#include "headers.h"

class Object;
class GraphicsEngine;

/// <summry>
/// Component 부모 클래스
/// 최초 작성일 : 2023/07/23
/// 최초 작성일 : 2023/07/23
/// 작성자 : 김형환
/// 
/// 모든 컴포넌트의 부모 클래스
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

