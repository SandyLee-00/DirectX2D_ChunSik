#pragma once
#include "Component.h"

class GraphicsEngine;

/// <summary>
/// 클릭 입력을 받고 처리하도록 하는 컴포넌트
/// 마우스 입력을 받기 위해서 붙힌다
/// BoxCollider 크기만큼 인식한다X -> SetSize로 크기 조절
/// </summary>

class MouseEvent : public Component
{
private:
	bool isMouseOn;
	bool isMouseLBTNUp;
	Vector2 size;

public:
	MouseEvent(Object* owner);
	virtual ~MouseEvent() override;

	virtual void Update(float _dt = 0) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;
	virtual void LateUpdate() override {};
	virtual void Render(GraphicsEngine* _graphicsEngine) override;

	void SetMouseOn(bool _isMouseOn) { isMouseOn = _isMouseOn; }
	void SetMouseLBTNUp(bool _isMouseLBTNDown) { isMouseLBTNUp = _isMouseLBTNDown; }
	void SetSize(Vector2 _size) { size = _size; }

	bool GetMouseOn() const { return isMouseOn; }
	bool GetMouseLBTNUp() const { return isMouseLBTNUp; }
	Vector2 GetSize() const { return size; }
};

