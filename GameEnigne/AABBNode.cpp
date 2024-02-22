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
/// 노드에 자식 노드 추가
/// </summary>
/// <param name="_a">자식 1</param>
/// <param name="_b">자식 2</param>
void AABBNode::AddChild(AABBNode* _a, AABBNode* _b)
{
	this->children[0] = _a;
	this->children[1] = _b;

	_a->parent = this;
	_b->parent = this;
}

/// <summary>
/// 해당 콜라이더의 노드를 만들고 리프로 만들기
/// </summary>
/// <param name="_collider">콜라이더</param>
void AABBNode::SetLeaf(Collider* _collider)
{
	this->collider = _collider;
	children[0] = nullptr;
	children[1] = nullptr;
}

/// <summary>
/// 업데이트
/// </summary>
/// <param name="_margine">여윳값</param>
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
/// 형제 노드 가져오기
/// </summary>
/// <returns>형제 노드</returns>
AABBNode* AABBNode::GetSibling()
{
	assert(this->parent);
	return this->parent->children[0] == this ? this->parent->children[1] : this->parent->children[0];
}
