#include "AABBNode.h"
#include "Collider.h"
AABBNode::AABBNode()
	: parent(nullptr)
	, children{ nullptr, nullptr }
	, crossedChildren(false)
	, aabb{}
	, collider(nullptr)
{

}

AABBNode::~AABBNode()
{

}

/// <summary>
/// ��忡 �ڽ� ��� �߰�
/// </summary>
/// <param name="_a">�ڽ� 1</param>
/// <param name="_b">�ڽ� 2</param>
void AABBNode::AddChild(AABBNode* _a, AABBNode* _b)
{
	this->children[0] = _a;
	this->children[1] = _b;

	_a->parent = this;
	_b->parent = this;
}

/// <summary>
/// �ش� �ݶ��̴��� ��带 ����� ������ �����
/// </summary>
/// <param name="_collider">�ݶ��̴�</param>
void AABBNode::SetLeaf(Collider* _collider)
{
	this->collider = _collider;
	children[0] = nullptr;
	children[1] = nullptr;
}

/// <summary>
/// ������Ʈ
/// </summary>
/// <param name="_margine">������</param>
void AABBNode::Update(float _margine)
{
	if (IsLeaf()) 
	{
		this->aabb.minPoint = this->collider->GetMinPoint() - Vector2{_margine, _margine};
		this->aabb.maxPoint = this->collider->GetMaxPoint() + Vector2{_margine, _margine};
	}
	else
	{
		this->aabb = children[0]->aabb.Union(children[1]->aabb);
	}
}

/// <summary>
/// ���� ��� ��������
/// </summary>
/// <returns>���� ���</returns>
AABBNode* AABBNode::GetSibling()
{
	assert(this->parent);
	return this->parent->children[0] == this ? this->parent->children[1] : this->parent->children[0];
}
