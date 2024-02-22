#include "Transform.h"

/// <summary>
/// ������
/// </summary>
/// <param name="owner">���ӵ� ������Ʈ</param>
/// <param name="_where">�ʱ� ��ġ</param>
Transform::Transform(Object* owner, Vector2 _where /*= { 0,0 }*/)
	: Component(CALL_ORDER::TRANSFORM, "Transform", owner)
{
	this->transformationMatrix = Matrix();
	this->SetPosition(_where);
}

/// <summary>
/// �Ҹ���
/// </summary>
Transform::~Transform()
{

}

/// <summary>
/// ������ �Լ�
/// </summary>
/// <param name="_distance">�ش� """�Ÿ�"""��ŭ �̵�</param>
void Transform::Translation(const Vector2& _distance)
{
	// �׵������ ������ �̵� ��� ����
	Matrix temp(4);

	temp[3][0] = _distance.x;
	temp[3][1] = _distance.y;
	temp[3][2] = 0.f;

	// �̵�
	this->transformationMatrix *=  temp;
}

void Transform::SetPosition(const Vector2& _distance)
{
	// �׵������ ������ �̵� ��� ����
	Matrix temp(4);

	temp[3][0] = _distance.x;
	temp[3][1] = _distance.y;
	temp[3][2] = 0.f;

	// �̵�
	this->transformationMatrix = temp;
}

/// <summary>
/// ȸ�� �Լ�
/// </summary>
/// <param name="_angle">���� (�Ϲݰ�)</param>
/// <param name="_axis">�� (x : 1 / y : 2 / z : 3) �⺻ z�� ȸ��</param>
void Transform::SetRotation(float _angle, int _axis)
{
	// �׵���� ���ϱ�
	Matrix temp(4);

	// ���� �࿡ ���� �� ����
	switch (_axis)
	{
		// x
		case 1:
		{
			temp[1][1] = cos(_angle);
			temp[1][2] = sin(_angle);
			temp[2][1] = -sin(_angle);
			temp[2][2] = cos(_angle);
		}
		break;

		// y
		case 2:
		{
			temp[0][0] = cos(_angle);
			temp[0][2] = sin(_angle);
			temp[2][0] = -sin(_angle);
			temp[2][2] = cos(_angle);
		}
		break;
		// z
		case 3:
		{
			temp[0][0] = cos(_angle);
			temp[0][1] = sin(_angle);
			temp[1][0] = -sin(_angle);
			temp[1][1] = cos(_angle);
		}
		break;
		default:
			break;
	}

	// ��ȯ ��Ŀ� ���ϱ�
	this->transformationMatrix *= temp;
}

/// <summary>
/// ȸ�� �Լ�
/// </summary>
/// <param name="_angle">���� (�Ϲݰ�)</param>
/// <param name="_center">�߽� ��</param>
/// <param name="_axis">ȸ�� ��</param>
void Transform::SetRotation(float _angle, const Vector2& _center, int _axis)
{
	// ���� �������� �������� �ű� �� ȸ�� �� �ٽ� ���� ��ġ�� �ű�� (TRT)
	SetPosition(_center);
	SetRotation(_angle, _axis);
	SetPosition(-_center);
}

/// <summary>
/// ũ�� ���� �Լ�
/// </summary>
/// <param name="_scale">"""����"""</param>
void Transform::SetScale(const Vector2& _scale)
{
	// �׵���� ���ϱ�
	Matrix temp(4);

	// ������ ��
	temp[0][0] *= _scale.x;
	temp[1][1] *= _scale.y;

	this->transformationMatrix *= temp;
	return;
}

/// <summary>
/// ��ü �������� ũ�� ���� �Լ�
/// </summary>
/// <param name="_scale">����</param>
/// <param name="_center">��</param>
void Transform::SetScale(const Vector2& _scale, const Vector2& _center)
{
	SetPosition(_center);
	SetScale(_scale);
	SetPosition(-_center);
}

/// <summary>
/// Vector2�� X, Y ��ǥ �˷��ֱ� (Z�� 0)
/// </summary>
/// <returns>��ǥ</returns>
Vector2 Transform::GetPosition() const
{
	return Vector2(this->transformationMatrix[3][0], this->transformationMatrix[3][1]);
}

/// <summary>
/// Vector2�� Scale �� �� ��ȯ 
/// </summary>
/// <returns></returns>
Vector2 Transform::GetScale() const
{
	return Vector2(this->transformationMatrix[0][0], this->transformationMatrix[1][1]);
}

/// <summary>
/// atanf(y / x )���� ���� ���� ��ȯ
/// </summary>
/// <param name="axis">��</param>
/// <returns>�Ϲݰ�</returns>
float Transform::GetRotation(int axis /*= 3*/) const
{
	const float PI = 3.141592f;
	
	// z�� ���� ȸ��
	float yaw = atan2(this->transformationMatrix[0][2], this->transformationMatrix[0][0]);
	yaw = yaw * 180 / PI;
	return yaw;

}
