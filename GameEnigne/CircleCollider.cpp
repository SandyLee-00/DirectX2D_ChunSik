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
/// �簢���� ���� �浹 ���
/// </summary>
/// <param name="_other">�浹ü</param>
/// <returns>�浹 ���</returns>
bool CircleCollider::IsCollision(BoxCollider* _other)
{
	return false;
}

/// <summary>
/// CC �浹
/// </summary>
/// <param name="_other">�浹ü</param>
/// <returns>CC ���</returns>
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
/// �ݶ��̴� ������Ʈ
/// ���� ������Ʈ ��ġ �Ѿư���
/// </summary>
/// <param name="_dt">dt</param>
void CircleCollider::Update(float _dt)
{
}

/// <summary>
/// ����� ������ ���� �Լ�
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
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
