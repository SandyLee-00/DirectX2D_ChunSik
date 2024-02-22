#include "CircleCollider.h"
#include "Object.h"
#include "Transform.h"
CircleCollider::CircleCollider(Object* _owner, float _radius)
	: Collider(_owner)
	, radius(_radius)
{
	this->shape = COLLIDER_SHPAE::CIRCLE;
}

CircleCollider::~CircleCollider()
{

}

/// <summary>
/// 사각형과 원의 충돌 결과
/// </summary>
/// <param name="_other">충돌체</param>
/// <returns>충돌 결과</returns>
bool CircleCollider::IsCollision(BoxCollider* _other)
{
	return false;
}

/// <summary>
/// CC 충돌
/// </summary>
/// <param name="_other">충돌체</param>
/// <returns>CC 결과</returns>
bool CircleCollider::IsCollision(CircleCollider* _other)
{
	float range = this->radius + _other->GetRadius();

	Matrix tPos = this->GetOwner()->GetComponent<Transform>()->GetTransformationMatrix();
	Matrix oPos = _other->GetOwner()->GetComponent<Transform>()->GetTransformationMatrix();

	float distance = (float)sqrt(pow(2, tPos[3][0] - oPos[3][0]) + pow(2, tPos[3][1] - oPos[3][1]));

	if (distance <= radius) 
	{
		return true;
	}
	return false;
}

bool CircleCollider::IsCollision(Vector2 _other)
{
	return false;
}

/// <summary>
/// 콜라이더 업데이트
/// 주인 오브젝트 위치 쫓아가기
/// </summary>
/// <param name="_dt">dt</param>
void CircleCollider::Update(float _dt)
{
}

/// <summary>
/// 디버깅 렌더에 쓰일 함수
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void CircleCollider::Render(GraphicsEngine* _graphicsEngine)
{
}

void CircleCollider::DebugRender(GraphicsEngine* _graphicsEngine)
{
}

Vector2 CircleCollider::GetMinPoint()
{
	return {};
}

Vector2 CircleCollider::GetMaxPoint()
{
	return {};
}
