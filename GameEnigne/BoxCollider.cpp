#include "BoxCollider.h"
#include "Object.h"
#include "Transform.h"

/// <summary>
/// 생성자
/// </summary>
/// <param name="owner">주인 오브젝트</param>
/// <param name="_xsclae">가로 크기</param>
/// <param name="_yscale">세로 크기</param>
/// <param name="_offset">오프셋</param>
BoxCollider::BoxCollider(Object* owner)
	: Collider(owner)
{
	this->shape = COLLIDER_SHPAE::BOX;
	// 위치 정보 입력
	SetSize();
}

BoxCollider::~BoxCollider()
{

}

/// <summary>
/// AABB 충돌 검출
/// </summary>
/// <param name="_other">충돌체</param>
/// <returns>AABB 결과</returns>
bool BoxCollider::IsCollision(BoxCollider* _other)
{
	if (this->globalVertices[0].x <= _other->GetGlobalVertices()[1].x &&
		this->globalVertices[1].x >= _other->GetGlobalVertices()[0].x &&
		this->globalVertices[0].y <= _other->GetGlobalVertices()[2].y &&
		this->globalVertices[2].y >= _other->GetGlobalVertices()[0].y
		)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 원과 사각형 충돌 검출
/// 미구현
/// </summary>
/// <param name="_other">충돌체</param>
/// <returns>충돌 결과</returns>
bool BoxCollider::IsCollision(CircleCollider* _other)
{
	return false;
}

bool BoxCollider::IsCollision(Vector2 _other)
{
	if (_other.x >= this->globalVertices[0].x && _other.y >= this->globalVertices[0].y &&
		_other.x <= this->globalVertices[2].x && _other.y <= this->globalVertices[2].y)
	{
		return true;
	}
	return false;
}

/// <summary>
/// 주인 오브젝트의 위치 따라가기
/// </summary>
void BoxCollider::Update(float _dt)
{
	Matrix global = this->GetOwner()->GetComponent<Transform>()->GetTransformationMatrix();
	for (size_t i = 0; i < this->localVertices.size(); i++)
	{
		this->globalVertices[i] = this->localVertices[i] * global;
	}
}

/// <summary>
/// 렌더에 쓰이는 렌더 함수
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void BoxCollider::Render(GraphicsEngine* _graphicsEngine)
{

}

/// <summary>
/// 디버깅 렌더에 쓰이는 렌더 함수
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void BoxCollider::DebugRender(GraphicsEngine* _graphicsEngine)
{
	_graphicsEngine->DrawEmptyRect(
		(int)(this->globalVertices[0].x),
		(int)(this->globalVertices[0].y),
		(int)(this->globalVertices[2].x),
		(int)(this->globalVertices[2].y));
}

/// <summary>
/// 크기 지정
/// 지정된 크기에 맞는 사각형 꼭지점 적용
/// 좌상 (0,0) 기준
/// </summary>
/// <param name="_size">크기 ( 가로 세로 )</param>
void BoxCollider::SetSize(Vector2 _size /*= {100, 100}*/)
{
	this->localVertices.clear();
	this->localVertices.shrink_to_fit();
	this->globalVertices.clear();
	this->localVertices.shrink_to_fit();

	this->localVertices.push_back((Vector2{ 0.0f, 0.0f } + this->GetOffset()));
	this->localVertices.push_back(Vector2{ _size.x, 0.0f } + this->GetOffset());
	this->localVertices.push_back(Vector2{ _size.x, _size.y } + this->GetOffset());
	this->localVertices.push_back(Vector2{ 0.0f, _size.y } + this->GetOffset());

	this->globalVertices.push_back(Vector2{ 0.0f, 0.0f } + this->GetOffset());
	this->globalVertices.push_back(Vector2{ _size.x, 0.0f } + this->GetOffset());
	this->globalVertices.push_back(Vector2{ _size.x, _size.y } + this->GetOffset());
	this->globalVertices.push_back(Vector2{ 0.0f, _size.y } + this->GetOffset());
	// 주인 오브젝트 따라가기
	Update();
}

/// <summary>
/// 크기 지정
/// </summary>
/// <param name="_width">넓이</param>
/// <param name="_height">높이</param>
void BoxCollider::SetSize(float _width, float _height)
{
	SetSize(Vector2(_width, _height));
}

/// <summary>
/// 크기 지정
/// </summary>
/// <param name="_width">넓이</param>
/// <param name="_height">높이</param>
void BoxCollider::SetSize(int _width, int _height)
{
	SetSize(Vector2((float)_width, (float)_height));
}

Vector2 BoxCollider::GetSize()
{
	float x = this->localVertices[1].x - this->localVertices[0].x;
	float y = this->localVertices[2].y - this->localVertices[1].y;
	return { x, y };
}

float BoxCollider::GetWidth()
{
	return this->localVertices[1].x - this->localVertices[0].x;
}

float BoxCollider::GetHeight()
{
	return this->localVertices[2].y - this->localVertices[1].y;
}

/// <summary>
/// 최소점 구하기 (좌상)
/// </summary>
/// <returns>좌상 값</returns>
Vector2 BoxCollider::GetMinPoint()
{
	return this->globalVertices[0];
}

/// <summary>
/// 최대점 구하기 (우하)
/// </summary>
/// <returns>(우하 값)</returns>
Vector2 BoxCollider::GetMaxPoint()
{
	return this->globalVertices[2];
}

