#include "Button.h"
#include "GraphicsEngine.h"
#include "MouseEvent.h"
#include "Transform.h"

Button::Button(ManagerSet* _manager)
	: Object("Button", _manager, OBJECT_TYPE::UI, {0, 0}),
	cnt(0)
{

}

Button::~Button()
{

}

void Button::Start()
{
	CreateComponent<MouseEvent>();
	MouseEvent* mouseEvent = this->GetComponent<MouseEvent>();
	mouseEvent->SetSize(this->size);
}

void Button::Update(float _deltaTime)
{
	MouseEvent* mouseEvent = this->GetComponent<MouseEvent>();
	if (mouseEvent->GetMouseLBTNUp())
	{
		OnButtonClicked();
	}
}

void Button::FinalUpdate(float _deltaTime)
{
	ComponentUpdate(_deltaTime);
}

/// <summary>
/// ��ư �׸��� �Լ�
/// </summary>
/// <param name="_graphicsEngine"></param>
void Button::Render(GraphicsEngine* _graphicsEngine)
{
	// Background Bar
}

void Button::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 leftTop = GetComponent<Transform>()->GetPosition();
	Vector2 rightBottom = leftTop + Vector2(size.x, size.y);

	_graphicsEngine->ColorSet(D2D1::ColorF::Red);
	_graphicsEngine->DrawEmptyRect(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

	// text cnt
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->DrawString((int)leftTop.x + 10, (int)leftTop.y - 10, std::to_string(cnt));

	// ���� ����� ������	
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	ComponentRender(_graphicsEngine);
}

/// <summary>
/// ��ư�� Ŭ������ ��
/// </summary>
void Button::OnButtonClicked()
{
	cnt++;
}
