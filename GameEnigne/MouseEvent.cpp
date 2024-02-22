#include "MouseEvent.h"
#include "Object.h"
#include "KeyManager.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "Vector2.h"
#include "GraphicsEngine.h"

MouseEvent::MouseEvent(Object* owner)
	: Component(CALL_ORDER::UI, "MouseEvent", owner)
	, isMouseOn(false)
	, isMouseLBTNUp(false)
{

}

MouseEvent::~MouseEvent()
{

}

void MouseEvent::Update(float _dt)
{
	KeyManager* keyManager = GetOwner()->GetManagers()->GetKeyManager();
	Transform* transform = GetOwner()->GetComponent<Transform>();

	// 마우스가 오브젝트 위에 있는지 확인
	Vector2 mousePosition = keyManager->GetMousePosition();
	Vector2 leftTop = transform->GetPosition();
	Vector2 rightBottom = transform->GetPosition() + Vector2(size.x, size.y);

	// 마우스가 오브젝트 위에 있는지 확인 && 마우스 왼쪽 버튼이 눌렸는지 확인
	if (mousePosition.x > leftTop.x && mousePosition.x < rightBottom.x &&
		mousePosition.y > leftTop.y && mousePosition.y < rightBottom.y &&
		keyManager->GetKeyState(KEY::LBTN) == KEY_STATE::UP )
	{
		isMouseOn = true;
		isMouseLBTNUp = true;
	}
	else if (mousePosition.x > leftTop.x && mousePosition.x < rightBottom.x &&
		mousePosition.y > leftTop.y && mousePosition.y < rightBottom.y)
	{
		isMouseOn = true;
		isMouseLBTNUp = false;
	}
	else
	{
		isMouseOn = false;
		isMouseLBTNUp = false;
	}
	
}

void MouseEvent::DebugRender(GraphicsEngine* _graphicsEngine)
{
	KeyManager* keyManager = GetOwner()->GetManagers()->GetKeyManager();
	Transform* transform = GetOwner()->GetComponent<Transform>();
	// 마우스가 오브젝트 위에 있는지 확인
	Vector2 mousePosition = keyManager->GetMousePosition();
	Vector2 leftTop = transform->GetPosition();
	Vector2 rightBottom = transform->GetPosition() + Vector2(size.x, size.y);
	if (isMouseOn == true && isMouseLBTNUp == false)
	{
		_graphicsEngine->ColorSet(D2D1::ColorF::AliceBlue);

	}
	if (isMouseOn == true && isMouseLBTNUp == true)
	{
		_graphicsEngine->ColorSet(D2D1::ColorF::Blue);

	}
	else if (isMouseOn == false)
	{
		_graphicsEngine->ColorSet(D2D1::ColorF::AntiqueWhite);

	}

	_graphicsEngine->DrawEmptyRect(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);
	_graphicsEngine->DrawCircle(mousePosition.x, mousePosition.y, 5.f, 5.f);
}

void MouseEvent::Render(GraphicsEngine* _graphicsEngine)
{

}
