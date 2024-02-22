#include "Transform.h"

/// <summary>
/// 생성자
/// </summary>
/// <param name="owner">종속된 오브젝트</param>
/// <param name="_where">초기 위치</param>
Transform::Transform(Object* owner, Vector2 _where /*= { 0,0 }*/)
	: Component(CALL_ORDER::TRANSFORM, "Transform", owner)
{
	this->transformationMatrix = Matrix();
	this->SetPosition(_where);
}

/// <summary>
/// 소멸자
/// </summary>
Transform::~Transform()
{

}

/// <summary>
/// 움직임 함수
/// </summary>
/// <param name="_distance">해당 """거리"""만큼 이동</param>
void Transform::Translation(const Vector2& _distance)
{
	// 항등행렬을 가져와 이동 행렬 구현
	Matrix temp(4);

	temp[3][0] = _distance.x;
	temp[3][1] = _distance.y;
	temp[3][2] = 0.f;

	// 이동
	this->transformationMatrix *=  temp;
}

void Transform::SetPosition(const Vector2& _distance)
{
	// 항등행렬을 가져와 이동 행렬 구현
	Matrix temp(4);

	temp[3][0] = _distance.x;
	temp[3][1] = _distance.y;
	temp[3][2] = 0.f;

	// 이동
	this->transformationMatrix = temp;
}

/// <summary>
/// 회전 함수
/// </summary>
/// <param name="_angle">각도 (일반각)</param>
/// <param name="_axis">축 (x : 1 / y : 2 / z : 3) 기본 z축 회전</param>
void Transform::SetRotation(float _angle, int _axis)
{
	// 항등행렬 구하기
	Matrix temp(4);

	// 최전 축에 따라 갑 지정
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

	// 변환 행렬에 곱하기
	this->transformationMatrix *= temp;
}

/// <summary>
/// 회전 함수
/// </summary>
/// <param name="_angle">각도 (일반각)</param>
/// <param name="_center">중심 축</param>
/// <param name="_axis">회전 축</param>
void Transform::SetRotation(float _angle, const Vector2& _center, int _axis)
{
	// 축을 기준으로 원점으로 옮긴 후 회전 후 다시 원래 위치로 옮기기 (TRT)
	SetPosition(_center);
	SetRotation(_angle, _axis);
	SetPosition(-_center);
}

/// <summary>
/// 크기 조절 함수
/// </summary>
/// <param name="_scale">"""비율"""</param>
void Transform::SetScale(const Vector2& _scale)
{
	// 항등행렬 구하기
	Matrix temp(4);

	// 스케일 값
	temp[0][0] *= _scale.x;
	temp[1][1] *= _scale.y;

	this->transformationMatrix *= temp;
	return;
}

/// <summary>
/// 물체 기준으로 크기 조절 함수
/// </summary>
/// <param name="_scale">비율</param>
/// <param name="_center">축</param>
void Transform::SetScale(const Vector2& _scale, const Vector2& _center)
{
	SetPosition(_center);
	SetScale(_scale);
	SetPosition(-_center);
}

/// <summary>
/// Vector2로 X, Y 좌표 알려주기 (Z는 0)
/// </summary>
/// <returns>좌표</returns>
Vector2 Transform::GetPosition() const
{
	return Vector2(this->transformationMatrix[3][0], this->transformationMatrix[3][1]);
}

/// <summary>
/// Vector2로 Scale 된 값 반환 
/// </summary>
/// <returns></returns>
Vector2 Transform::GetScale() const
{
	return Vector2(this->transformationMatrix[0][0], this->transformationMatrix[1][1]);
}

/// <summary>
/// atanf(y / x )으로 구한 각도 반환
/// </summary>
/// <param name="axis">축</param>
/// <returns>일반각</returns>
float Transform::GetRotation(int axis /*= 3*/) const
{
	const float PI = 3.141592f;
	
	// z축 기준 회전
	float yaw = atan2(this->transformationMatrix[0][2], this->transformationMatrix[0][0]);
	yaw = yaw * 180 / PI;
	return yaw;

}
