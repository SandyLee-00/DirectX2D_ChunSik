#pragma once
#include "Component.h"

class GraphicsEngine;

/// <summary>
/// Ŭ�� �Է��� �ް� ó���ϵ��� �ϴ� ������Ʈ
/// ���콺 �Է��� �ޱ� ���ؼ� ������
/// BoxCollider ũ�⸸ŭ �ν��Ѵ�X -> SetSize�� ũ�� ����
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

