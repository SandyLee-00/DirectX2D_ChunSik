#include "AABBTree.h"
#include "Collider.h"
#include "Object.h"
#include "CollisionManager.h"

AABBTree::AABBTree(float _margin, CollisionManager* _collisionManger)
	: root(nullptr)
	, pairs{}
	, margin(_margin)
	, collisionManager(_collisionManger)
	, invalidNodes{}
	, removeNodes{}
{

}

AABBTree::~AABBTree()
{
	Clear();
}

/// <summary>
/// ���ο� �ݸ��̴��� Ʈ���� �Է�
/// </summary>
/// <param name="_collider">�ݶ��̴�</param>
void AABBTree::AddCollider(Collider* _collider)
{
	// �� ���
	AABBNode* node = new AABBNode();

	// Node �� Collider ����
	_collider->SetNode(node);
	node->collider = _collider;

	// ��Ʈ�� �ִ� ���
	if (this->root)
	{
		// �� ��带 ���� ���� ����� Ʈ���� �Է�
		node->SetLeaf(_collider);
		node->Update(this->margin);
		InsertNode(node, &this->root);
	}
	// ��Ʈ�� ���� ���
	else
	{
		// �� ��带 ��Ʈ��
		this->root = node;
		this->root->SetLeaf(_collider);
		this->root->Update(this->margin);
	}
}

/// <summary>
/// �ش� �ݶ��̴��� ��� ����
/// </summary>
/// <param name="_collider">������ �ݶ��̴�</param>
void AABBTree::RemoveCollider(Collider* _collider)
{
	// �ݶ��̴��� ��� ��������
	AABBNode* node = _collider->GetNode();

	// �ش� ����� �ݶ��̴� �����
	node->collider = nullptr;
	// �ݶ��̴��� �ִ� ��� ���� �����
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

/// <summary>
/// ������Ʈ
/// AABB tree �� ��带 ��� ������Ʈ �Ѵ�
/// </summary>
void AABBTree::Update()
{
	// ��Ʈ ���� ���� ����
	if (this->root)
	{
		// ���� ��Ʈ�� �ٷ� ������ ���
		if (this->root->IsLeaf())
		{
			// ��Ʈ ��尡 ���������� ���
			if (!this->root->collider->GetOwner()->IsAlive())
			{
				RemoveCollider(this->root->collider);
			}
			// ��Ʈ ��尡 ���� ������ �ƴ� ��� ��Ʈ��� ������Ʈ
			else
			{
				this->root->Update(this->margin);
			}

		}
		// ���� ��Ʈ ��尡 ������ �ƴ� ���
		else
		{
			// �ϴ� �ʱ�ȭ
			this->invalidNodes.clear();
			this->removeNodes.clear();
			// �ʱ�ȭ �� �ٽ� ��ȿ, ���� ���� ���ϱ�
			UpdateAllNode(this->root);

			// ���������� ������Ʈ�� Ʈ������ ����
			for (AABBNode* node : this->removeNodes)
			{
				RemoveCollider(node->collider);
			}

			// ��ȿ���� �ʴ� ��� ��带 �ٽ� ����
			for (AABBNode* node : this->invalidNodes)
			{
				// ���� ��带 �θ� ���� �°�
				// ���� �θ� ��带 ����
				// ���� ��带 �ٽ� Ʈ���� �ֱ�

				// �θ�
				AABBNode* parent = node->parent;
				// ����
				AABBNode* siblibg = node->GetSibling();
				// �θ� ��ũ ��� (�θ� ����Ű�� �����͸� ����Ű�� ������) ���θ� ���ٸ� ��Ʈ�� �ּҸ� �����´�
				AABBNode** parentLink = parent->parent
					? (parent == parent->parent->children[0]
						? &parent->parent->children[0]
						: &parent->parent->children[1])
					: &this->root;

				// ���� ����� �θ� ���θ� ���� ��ü
				siblibg->parent = parent->parent ? parent->parent : nullptr;

				*parentLink = siblibg;
				delete parent;

				// re-insert node 
				// Ʈ���� �ٽ�Ȯ�� 
				node->Update(this->margin);
				InsertNode(node, &this->root);
			}
			this->invalidNodes.clear();
			this->removeNodes.clear();
		}

	}
}

/// <summary>
/// �ش� �浹ü�� Ʈ������ ����
/// </summary>
/// <param name="_collider">�浹ü</param>
void AABBTree::Remove(Collider* _collider)
{
	// �浹ü���� ��� ��������
	AABBNode* node = _collider->GetNode();

	// remove two-way link
	node->collider = nullptr;
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

/// <summary>
/// �浹 ���ɼ��� �ִ� ���� �����´�
/// </summary>
/// <returns>�浹 ���ɼ��� �ִ� ��</returns>
std::list<std::pair<Collider*, Collider*>>& AABBTree::GetCollisionPairs()
{
	// �ϴ� �ʱ�ȭ
	this->pairs.clear();
	this->pairs = std::list<std::pair<Collider*, Collider*>>();
	// ��Ʈ ��尡 ���ų� ������� ���
	if (!this->root || this->root->IsLeaf())
	{
		return this->pairs;
	}

	// ��� ��忡 ���ؼ� �浹 ���� �ʱ�ȭ
	ClearChildrenCrossFlag(this->root);

	// base recursive call
	// ������� ȣ��
	ComputeCollisionPairs(this->root->children[0], this->root->children[1]);

	return this->pairs;
}

/// <summary>
/// �� ���� �浹�ϴ� ��� �ݶ��̴� ��������
/// </summary>
/// <param name="_point">��</param>
/// <param name="_colliderVector">�浹ü ����</param>
void AABBTree::Pick(const Vector2& _point, std::vector<Collider*>& _colliderVector)
{
	// ��� ť
	std::queue<AABBNode*> q;

	// ���� ��Ʈ�� �ִٸ� ��Ʈ�� �ִ´�.
	if (this->root)
	{
		q.push(this->root);
	}

	// ť�� �� ������
	while (!q.empty())
	{
		// ť�� �ִ� ��带 ������
		assert(q.front() != nullptr && "Somethig Worng At Collision Detect (Rect to Point)");
		AABBNode& node = *q.front();
		q.pop();

		// ��尡 �������
		if (node.IsLeaf())
		{
			// ���� �浹�ϴ� ���
			if (node.collider->IsCollision(_point))
			{
				_colliderVector.push_back(node.collider);
			}
		}
		// ������ �ƴ϶�� �ڽ��� Ǫ��
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}
}

/// <summary>
/// �� AABB�� �浹�ϴ� ��� �ݶ��̴� ��������
/// </summary>
/// <param name="_aabb">AABB</param>
/// <param name="_colliderVector">�浹ü ����</param>
void AABBTree::Query(const AABB& _aabb, std::vector<Collider*>& _output) const
{
	std::queue<AABBNode*> q;

	// ��Ʈ�� �ִٸ� ť�� �ֱ�
	if (this->root)
	{
		q.push(this->root);
	}

	// ť�� �� ������ �ݺ�
	while (!q.empty())
	{
		assert(q.front() != nullptr && "Somethig Worng At Collision Detect (Rect to Rect)");
		AABBNode& node = *q.front();
		q.pop();
		
		// ���� �����
		if (node.IsLeaf())
		{
			// AABB �浹
			Vector2 leftMax = node.collider->GetMaxPoint();
			Vector2 leftMin = node.collider->GetMinPoint();

			Vector2 rightMax = _aabb.maxPoint;
			Vector2 rightMin = _aabb.minPoint;

			if (leftMin.x <= rightMax.x && leftMax.x >= rightMin.x
				&& leftMin.y <= rightMax.y && leftMax.y >= rightMin.y)
			{
				_output.push_back(node.collider);
			}
		}
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}

}

/// <summary>
/// Ʈ���� �ʱ�ȭ
/// </summary>
void AABBTree::Clear()
{
	// BFS �Ҹ� 
	std::queue<AABBNode*> q;

	if (this->root)
	{
		q.push(this->root);
	}

	while (!q.empty())
	{
		AABBNode* node = q.front();
		q.pop();

		if (node->children[0])
		{
			q.push(node->children[0]);
			q.push(node->children[1]);
		}
		delete node;
	}
	this->root = nullptr;

}

/// <summary>
/// AABB Ʈ���� ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void AABBTree::DebugRender(GraphicsEngine* _graphicsEngine)
{
	std::queue<AABBNode*> q;

	if (this->root)
		q.push(this->root);

	while (!q.empty())
	{
		AABBNode* node = q.front();
		q.pop();

		// ������

		if (node->IsLeaf())
		{
			_graphicsEngine->ColorSet(D2D1::ColorF::Red);
			_graphicsEngine->DrawEmptyRect(node->aabb.minPoint.x, node->aabb.minPoint.y, node->aabb.maxPoint.x, node->aabb.maxPoint.y);
		}
		else
		{
			_graphicsEngine->ColorSet(D2D1::ColorF::Red);
			_graphicsEngine->DrawEmptyRect(node->aabb.minPoint.x, node->aabb.minPoint.y, node->aabb.maxPoint.x, node->aabb.maxPoint.y);;
			q.push(node->children[0]);
			q.push(node->children[1]);
		}

	}
}

// RayCastResult AABBTree::RayCast(const Vector2& _direct, const Vector2& _center, float _maxDistance /*= 0.f*/) const
// {
// 
// }

/// <summary>
/// ��� ������Ʈ
/// </summary>
/// <param name="_node"> ���� �������, �� �� �Ϲ� ���</param>
void AABBTree::UpdateAllNode(AABBNode* _node)
{
	// ���� �����
	if (_node->IsLeaf())
	{
		// ���� ������ ������Ʈ���
		if (!_node->collider->GetOwner()->IsAlive())
		{
			// ������ ��庤�Ϳ� �ֱ�
			this->removeNodes.push_back(_node);
		}
		// ���� ������ �ƴϰ�, ����� AABB�ȿ� �ݶ��̴��� ���ٸ�
		else if (!_node->aabb.Contains(_node->collider))
		{
			// ��ȿ���� ���� ��庤�Ϳ� �ֱ�
			this->invalidNodes.push_back(_node);
		}
	}
	// ������尡 �ƴ϶��
	else
	{
		// ���
		UpdateAllNode(_node->children[0]);
		UpdateAllNode(_node->children[1]);
	}
}

/// <summary>
/// ��带 �ش� �θ� �׿� �ֱ�
/// �ִ��� ���� ũ�Ⱑ �ǵ��� ����� �浹 ���� Ƚ���� ���δ�
/// </summary>
/// <param name="_node">���</param>
/// <param name="_parent">�θ��� �ּ�</param>
void AABBTree::InsertNode(AABBNode* _node, AABBNode** _parent)
{
	// �θ� ���
	AABBNode* p = *_parent;
	// �θ� ��尡 ������� ���
	if (p->IsLeaf())
	{
		// �� �θ� ��带 ����
		AABBNode* newParent = new AABBNode();
		// �� �θ� ����� �θ� �θ��� �θ� ���� ����
		newParent->parent = p->parent;
		// �� �θ� ��忡 �ڽŰ� ���� �θ� ��带 �ڽ����� ����
		newParent->AddChild(_node, p);
		// �θ� ��带 �� �θ� ���� �ٲ�
		*_parent = newParent;
	}
	// �θ� ��尡 ������ �ƴ϶��
	else
	{
		// �θ� �귣ġ�̸�, �������� ���� �������̸� ���
		// �θ����� �ڽ� �� ����ʿ� ��ġ�°� �� ũ�Ⱑ ���� ��尡 �Ǵ��� ���
		const AABB aabb0 = p->children[0]->aabb;
		const AABB aabb1 = p->children[1]->aabb;

		const float volumeDiff0 = aabb0.Union(_node->aabb).GetArea() - aabb0.GetArea();
		const float volumeDiff1 = aabb1.Union(_node->aabb).GetArea() - aabb1.GetArea();

		// ���� ������ ���� �ڽĳ�忡�� �����Ѵ�.
		if (volumeDiff0 < volumeDiff1)
		{
			InsertNode(_node, &p->children[0]);
		}
		else
		{
			InsertNode(_node, &p->children[1]);
		}
	}

	// �θ� AABB ������Ʈ (������� ȣ��)
	(*_parent)->Update(this->margin);
}

/// <summary>
/// ���� ���� ��� �ڽ� ��� ����
/// </summary>
/// <param name="_node">���</param>
void AABBTree::RemoveNode(AABBNode* _node)
{
	// �θ� ��� ��������
	AABBNode* parent = _node->parent;

	// ���� ��尡 ��Ʈ�� �ƴ϶��
	if (parent)
	{
		// ���� ��� ��������
		AABBNode* sibling = _node->GetSibling();
		// ���� ���θ� ��尡 �ִٸ�
		if (parent->parent)
		{
			// ���� ����� �θ� ���θ� ���� ����
			sibling->parent = parent->parent;
			(parent == parent->parent->children[0]
				? parent->parent->children[0]
				: parent->parent->children[1]) = sibling;
		}
		// ������ ��尡 ���ٸ�
		else
		{
			// ���� ��带 ��Ʈ ���� ����
			this->root = sibling;
			sibling->parent = nullptr;
		}
		// ���� ���� �θ� ��带 ����
		delete _node;
		delete parent;
	}
	// ��Ʈ���
	else
	{
		// �׳� ����
		this->root = nullptr;
		delete _node;
	}
}

/// <summary>
/// �浹�ϴ� ���� ���
/// </summary>
/// <param name="_n0">��� 0</param>
/// <param name="_n1">��� 1</param>
void AABBTree::ComputeCollisionPairs(AABBNode* _n0, AABBNode* _n1)
{
	// �� ��尡 ���������
	if (_n0->IsLeaf())
	{
		// �� �� ��������� �ٷ� ���Ѵ� ( �ݶ��̴��� �ִ� AABB �̹Ƿ� )
		if (_n1->IsLeaf())
		{
			// �浹�ϴ� Ÿ������ Ȯ���ϰ�, ������ �浹�ϴ� �� Ȯ���Ѵ�
			if (this->collisionManager->CheckType(_n0->collider->GetOwner()->GetType(), _n1->collider->GetOwner()->GetType()) &&
				_n0->collider->Collides(_n1->collider) && 
				_n0->collider->GetOwner() != _n1->collider->GetOwner())
			{
				// �浹�ϸ� �浹�ֿ� �ִ´�
				this->pairs.push_back(std::make_pair(_n0->collider, _n1->collider));
			}
		}
		// 1���� ������ ���
		else
		{
			// ������ �ƴ� ����� �ڽĿ� ���� üũ
			CrossChildren(_n1);

			// �� ����� AABB�� �浹�ϴ���
			if (!_n0->aabb.IsCollision(_n1->aabb))
			{
				return;
			}

			// �浹�Ѵٸ� ��������� ��� Ž��
			ComputeCollisionPairs(_n0, _n1->children[0]);
			ComputeCollisionPairs(_n0, _n1->children[1]);
		}
	}
	// �� ��尡 ���� ��尡 �ƴ϶��
	else
	{
		// ���� �ϳ��� ��������� ( �� )
		if (_n1->IsLeaf())
		{
			CrossChildren(_n0);
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			ComputeCollisionPairs(_n0->children[0], _n1);
			ComputeCollisionPairs(_n0->children[1], _n1);
		}
		// �� �� ���� ��尡 �ƴ϶��
		else
		{
			// �� ����� �ڽ� ������ ���� üũ
			CrossChildren(_n0);
			CrossChildren(_n1);

			// �� AABB�� �浹�ϴ���
			if (!_n0->aabb.IsCollision(_n1->aabb))
			{
				return;
			}

			// �浹�Ѵٸ� �ڽĿ� ���ؼ� ���� üũ
			ComputeCollisionPairs(_n0->children[0], _n1->children[0]);
			ComputeCollisionPairs(_n0->children[0], _n1->children[1]);
			ComputeCollisionPairs(_n0->children[1], _n1->children[0]);
			ComputeCollisionPairs(_n0->children[1], _n1->children[1]);
		}
	}
}

/// <summary>
/// �ش� ����� ��� �ڽĿ� ���� �浹 ���� �ʱ�ȭ
/// </summary>
/// <param name="_node">���� �������, ���� ���</param>
void AABBTree::ClearChildrenCrossFlag(AABBNode* _node)
{
	// �˻� ���� �ʱ�ȭ
	_node->crossedChildren = false;
	if (!_node->IsLeaf())
	{
		ClearChildrenCrossFlag(_node->children[0]);
		ClearChildrenCrossFlag(_node->children[1]);
	}
}

/// <summary>
/// �ش� ����� ��� �ڽ� ��忡 ���� �浹 �˻�
/// </summary>
/// <param name="_node">���</param>
void AABBTree::CrossChildren(AABBNode* _node)
{
	// �ش� ����� �ڽĿ� ���ؼ� �浹 �˻�
	// �̹� �˻� �� ����� ����
	if (!_node->crossedChildren)
	{
		ComputeCollisionPairs(_node->children[0], _node->children[1]);
		_node->crossedChildren = true;
	}
}
