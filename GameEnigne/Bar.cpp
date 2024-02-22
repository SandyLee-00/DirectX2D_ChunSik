#include "Bar.h"
#include "Transform.h"

Bar::Bar(ManagerSet* _manager)
	:Object("Bar", _manager, OBJECT_TYPE::UI, { 0, 0 }),
	value(1.0f),
	parent(nullptr)
{

}

Bar::~Bar()
{

}

void Bar::Start()
{

}

void Bar::Update(float _deltaTime)
{
	value -= _deltaTime;
	if(value < 0.0f)
		value = 1.0f;
}

void Bar::FinalUpdate(float _deltaTime)
{
	ComponentUpdate(_deltaTime);

	// 부모의 위치에 맞게 조정하기
	Transform* transform = GetComponent<Transform>();

	if (parent != nullptr)
	{
		Transform* parentTransform = parent->GetComponent<Transform>();
		transform->SetPosition(parentTransform->GetPosition());
	}
}

void Bar::Render(GraphicsEngine* _graphicsEngine)
{
	// Background Bar
	Vector2 leftTop = GetComponent<Transform>()->GetPosition() + offset;
	Vector2 rightBottom = leftTop + size;

	_graphicsEngine->ColorSet(D2D1::ColorF::Cornsilk);
	_graphicsEngine->DrawRectangle(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

	// Fill Bar
	Vector2 fillLeftTop = leftTop;
	Vector2 fillRightBottom = leftTop + Vector2(size.x * value, size.y);

	_graphicsEngine->ColorSet(D2D1::ColorF::Red);
	_graphicsEngine->DrawRectangle(fillLeftTop.x, fillLeftTop.y, fillRightBottom.x, fillRightBottom.y);

	// 원래 색깔로 돌리기
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
}

void Bar::DebugRender(GraphicsEngine* _graphicsEngine)
{

}
