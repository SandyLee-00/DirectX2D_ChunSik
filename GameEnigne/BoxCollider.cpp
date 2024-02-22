#include "BoxCollider.h"
#include "Object.h"
#include "Transform.h"

/// <summary>
/// ������
/// </summary>
/// <param name="owner">���� ������Ʈ</param>
/// <param name="_xsclae">���� ũ��</param>
/// <param name="_yscale">���� ũ��</param>
/// <param name="_offset">������</param>
BoxCollider::BoxCollider(Object* owner)
	: Collider(owner)
{
	this->shape = COLLIDER_SHPAE::BOX;
	// ��ġ ���� �Է�
	SetSize();
}

BoxCollider::~BoxCollider()
{

}

/// <summary>
/// AABB �浹 ����
/// </summary>
/// <param name="_other">�浹ü</param>
/// <returns>AABB ���</returns>
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
/// ���� �簢�� �浹 ����
/// �̱���
/// </summary>
/// <param name="_other">�浹ü</param>
/// <returns>�浹 ���</returns>
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
/// ���� ������Ʈ�� ��ġ ���󰡱�
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
/// ������ ���̴� ���� �Լ�
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void BoxCollider::Render(GraphicsEngine* _graphicsEngine)
{

}

/// <summary>
/// ����� ������ ���̴� ���� �Լ�
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void BoxCollider::DebugRender(GraphicsEngine* _graphicsEngine)
{
	_graphicsEngine->DrawEmptyRect(
		(int)(this->globalVertices[0].x),
		(int)(this->globalVertices[0].y),
		(int)(this->globalVertices[2].x),
		(int)(this->globalVertices[2].y));
}

/// <summary>
/// ũ�� ����
/// ������ ũ�⿡ �´� �簢�� ������ ����
/// �»� (0,0) ����
/// </summary>
/// <param name="_size">ũ�� ( ���� ���� )</param>
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
	// ���� ������Ʈ ���󰡱�
	Update();
}

/// <summary>
/// ũ�� ����
/// </summary>
/// <param name="_width">����</param>
/// <param name="_height">����</param>
void BoxCollider::SetSize(float _width, float _height)
{
	SetSize(Vector2(_width, _height));
}

/// <summary>
/// ũ�� ����
/// </summary>
/// <param name="_width">����</param>
/// <param name="_height">����</param>
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
/// �ּ��� ���ϱ� (�»�)
/// </summary>
/// <returns>�»� ��</returns>
Vector2 BoxCollider::GetMinPoint()
{
	return this->globalVertices[0];
}

/// <summary>
/// �ִ��� ���ϱ� (����)
/// </summary>
/// <returns>(���� ��)</returns>
Vector2 BoxCollider::GetMaxPoint()
{
	return this->globalVertices[2];
}

