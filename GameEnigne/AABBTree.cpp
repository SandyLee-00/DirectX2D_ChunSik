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
/// 새로운 콜리이더를 트리에 입력
/// </summary>
/// <param name="_collider">콜라이더</param>
void AABBTree::AddCollider(Collider* _collider)
{
	// 새 노드
	AABBNode* node = new AABBNode();

	// Node 와 Collider 연결
	_collider->SetNode(node);
	node->collider = _collider;

	// 루트가 있는 경우
	if (this->root)
	{
		// 이 노드를 리프 노드로 만들고 트리에 입력
		node->SetLeaf(_collider);
		node->Update(this->margin);
		InsertNode(node, &this->root);
	}
	// 루트가 없는 경우
	else
	{
		// 이 노드를 루트로
		this->root = node;
		this->root->SetLeaf(_collider);
		this->root->Update(this->margin);
	}
}

/// <summary>
/// 해당 콜라이더의 노드 제거
/// </summary>
/// <param name="_collider">제거할 콜라이더</param>
void AABBTree::RemoveCollider(Collider* _collider)
{
	// 콜라이더의 노드 가져오기
	AABBNode* node = _collider->GetNode();

	// 해당 노드의 콜라이더 지우기
	node->collider = nullptr;
	// 콜라이더에 있는 노드 정보 지우기
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

/// <summary>
/// 업데이트
/// AABB tree 의 노드를 모두 업데이트 한다
/// </summary>
void AABBTree::Update()
{
	// 루트 에서 부터 시작
	if (this->root)
	{
		// 만약 루트가 바로 말단인 경우
		if (this->root->IsLeaf())
		{
			// 루트 노드가 삭제예정인 경우
			if (!this->root->collider->GetOwner()->IsAlive())
			{
				RemoveCollider(this->root->collider);
			}
			// 루트 노드가 삭제 예정이 아닌 경우 루트노드 업데이트
			else
			{
				this->root->Update(this->margin);
			}

		}
		// 만약 루트 노드가 말단이 아닌 경우
		else
		{
			// 일단 초기화
			this->invalidNodes.clear();
			this->removeNodes.clear();
			// 초기화 후 다시 유효, 삭제 노드들 구하기
			UpdateAllNode(this->root);

			// 삭제예정인 오브젝트를 트리에서 제거
			for (AABBNode* node : this->removeNodes)
			{
				RemoveCollider(node->collider);
			}

			// 유효하지 않는 모든 노드를 다시 삽입
			for (AABBNode* node : this->invalidNodes)
			{
				// 형제 노드를 부모 노드로 승격
				// 원래 부모 노드를 제거
				// 원래 노드를 다시 트리에 넣기

				// 부모
				AABBNode* parent = node->parent;
				// 형제
				AABBNode* siblibg = node->GetSibling();
				// 부모 링크 잡기 (부모를 가리키는 포인터를 가리키는 포인터) 조부모가 없다면 루트의 주소를 가져온다
				AABBNode** parentLink = parent->parent
					? (parent == parent->parent->children[0]
						? &parent->parent->children[0]
						: &parent->parent->children[1])
					: &this->root;

				// 형제 노드의 부모를 조부모 노드로 교체
				siblibg->parent = parent->parent ? parent->parent : nullptr;

				*parentLink = siblibg;
				delete parent;

				// re-insert node 
				// 트리에 다시확장 
				node->Update(this->margin);
				InsertNode(node, &this->root);
			}
			this->invalidNodes.clear();
			this->removeNodes.clear();
		}

	}
}

/// <summary>
/// 해당 충돌체를 트리에서 제거
/// </summary>
/// <param name="_collider">충돌체</param>
void AABBTree::Remove(Collider* _collider)
{
	// 충돌체에서 노드 가져오기
	AABBNode* node = _collider->GetNode();

	// remove two-way link
	node->collider = nullptr;
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

/// <summary>
/// 충돌 가능성이 있는 쌍을 가져온다
/// </summary>
/// <returns>충돌 가능성이 있는 쌍</returns>
std::list<std::pair<Collider*, Collider*>>& AABBTree::GetCollisionPairs()
{
	// 일단 초기화
	this->pairs.clear();
	this->pairs = std::list<std::pair<Collider*, Collider*>>();
	// 루트 노드가 없거나 리프노드 라면
	if (!this->root || this->root->IsLeaf())
	{
		return this->pairs;
	}

	// 모든 노드에 대해서 충돌 정보 초기화
	ClearChildrenCrossFlag(this->root);

	// base recursive call
	// 재귀적인 호출
	ComputeCollisionPairs(this->root->children[0], this->root->children[1]);

	return this->pairs;
}

/// <summary>
/// 한 점과 충돌하는 모든 콜라이더 가져오기
/// </summary>
/// <param name="_point">점</param>
/// <param name="_colliderVector">충돌체 벡터</param>
void AABBTree::Pick(const Vector2& _point, std::vector<Collider*>& _colliderVector)
{
	// 노드 큐
	std::queue<AABBNode*> q;

	// 만일 루트가 있다면 루트를 넣는다.
	if (this->root)
	{
		q.push(this->root);
	}

	// 큐가 빌 때까지
	while (!q.empty())
	{
		// 큐에 있는 노드를 가져옴
		assert(q.front() != nullptr && "Somethig Worng At Collision Detect (Rect to Point)");
		AABBNode& node = *q.front();
		q.pop();

		// 노드가 리프라면
		if (node.IsLeaf())
		{
			// 만약 충돌하는 경우
			if (node.collider->IsCollision(_point))
			{
				_colliderVector.push_back(node.collider);
			}
		}
		// 리프가 아니라면 자식을 푸시
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}
}

/// <summary>
/// 한 AABB과 충돌하는 모든 콜라이더 가져오기
/// </summary>
/// <param name="_aabb">AABB</param>
/// <param name="_colliderVector">충돌체 벡터</param>
void AABBTree::Query(const AABB& _aabb, std::vector<Collider*>& _output) const
{
	std::queue<AABBNode*> q;

	// 루트가 있다면 큐에 넣기
	if (this->root)
	{
		q.push(this->root);
	}

	// 큐가 빌 때까지 반복
	while (!q.empty())
	{
		assert(q.front() != nullptr && "Somethig Worng At Collision Detect (Rect to Rect)");
		AABBNode& node = *q.front();
		q.pop();
		
		// 말단 노드라면
		if (node.IsLeaf())
		{
			// AABB 충돌
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
/// 트리의 초기화
/// </summary>
void AABBTree::Clear()
{
	// BFS 소멸 
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
/// AABB 트리를 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void AABBTree::DebugRender(GraphicsEngine* _graphicsEngine)
{
	std::queue<AABBNode*> q;

	if (this->root)
		q.push(this->root);

	while (!q.empty())
	{
		AABBNode* node = q.front();
		q.pop();

		// 랜더링

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
/// 노드 업데이트
/// </summary>
/// <param name="_node"> 최초 루프노드, 그 후 일반 노드</param>
void AABBTree::UpdateAllNode(AABBNode* _node)
{
	// 리프 노드라면
	if (_node->IsLeaf())
	{
		// 삭제 예정인 오브젝트라면
		if (!_node->collider->GetOwner()->IsAlive())
		{
			// 삭제될 노드벡터에 넣기
			this->removeNodes.push_back(_node);
		}
		// 삭제 예정이 아니고, 노드의 AABB안에 콜라이더가 없다면
		else if (!_node->aabb.Contains(_node->collider))
		{
			// 유효하지 않은 노드벡터에 넣기
			this->invalidNodes.push_back(_node);
		}
	}
	// 리프노드가 아니라면
	else
	{
		// 재귀
		UpdateAllNode(_node->children[0]);
		UpdateAllNode(_node->children[1]);
	}
}

/// <summary>
/// 노드를 해당 부모 및에 넣기
/// 최대한 작은 크기가 되도록 만들어 충돌 검출 횟수를 줄인다
/// </summary>
/// <param name="_node">노드</param>
/// <param name="_parent">부모의 주소</param>
void AABBTree::InsertNode(AABBNode* _node, AABBNode** _parent)
{
	// 부모 노드
	AABBNode* p = *_parent;
	// 부모 노드가 리프노드 라면
	if (p->IsLeaf())
	{
		// 새 부모 노드를 만듬
		AABBNode* newParent = new AABBNode();
		// 새 부모 노드의 부모를 부모의 부모 노드로 설정
		newParent->parent = p->parent;
		// 새 부모 노드에 자신과 현재 부모 노드를 자식으로 넣음
		newParent->AddChild(_node, p);
		// 부모 노드를 새 부모 노드로 바꿈
		*_parent = newParent;
	}
	// 부모 노드가 리프가 아니라면
	else
	{
		// 부모가 브랜치이면, 삽입전과 후의 넓이차이를 계산
		// 부모노드의 자식 중 어느쪽에 합치는게 더 크기가 작은 노드가 되는지 계산
		const AABB aabb0 = p->children[0]->aabb;
		const AABB aabb1 = p->children[1]->aabb;

		const float volumeDiff0 = aabb0.Union(_node->aabb).GetArea() - aabb0.GetArea();
		const float volumeDiff1 = aabb1.Union(_node->aabb).GetArea() - aabb1.GetArea();

		// 볼륨 증가가 적은 자식노드에게 삽입한다.
		if (volumeDiff0 < volumeDiff1)
		{
			InsertNode(_node, &p->children[0]);
		}
		else
		{
			InsertNode(_node, &p->children[1]);
		}
	}

	// 부모 AABB 업데이트 (재귀적인 호출)
	(*_parent)->Update(this->margin);
}

/// <summary>
/// 현재 노드와 모든 자식 노드 제거
/// </summary>
/// <param name="_node">노드</param>
void AABBTree::RemoveNode(AABBNode* _node)
{
	// 부모 노드 가져오기
	AABBNode* parent = _node->parent;

	// 현재 노드가 루트가 아니라면
	if (parent)
	{
		// 형제 노드 가져오기
		AABBNode* sibling = _node->GetSibling();
		// 만일 조부모 노드가 있다면
		if (parent->parent)
		{
			// 형제 노드의 부모를 조부모 노드로 변경
			sibling->parent = parent->parent;
			(parent == parent->parent->children[0]
				? parent->parent->children[0]
				: parent->parent->children[1]) = sibling;
		}
		// 조무모 노드가 없다면
		else
		{
			// 형제 노드를 루트 노드로 변경
			this->root = sibling;
			sibling->parent = nullptr;
		}
		// 현제 노드와 부모 노드를 제거
		delete _node;
		delete parent;
	}
	// 루트라면
	else
	{
		// 그냥 제거
		this->root = nullptr;
		delete _node;
	}
}

/// <summary>
/// 충돌하는 쌍을 계산
/// </summary>
/// <param name="_n0">노드 0</param>
/// <param name="_n1">노드 1</param>
void AABBTree::ComputeCollisionPairs(AABBNode* _n0, AABBNode* _n1)
{
	// 한 노드가 리프노드라면
	if (_n0->IsLeaf())
	{
		// 둘 다 리프노드라면 바로 비교한다 ( 콜라이더만 있는 AABB 이므로 )
		if (_n1->IsLeaf())
		{
			// 충돌하는 타입인지 확인하고, 실제로 충돌하는 지 확인한다
			if (this->collisionManager->CheckType(_n0->collider->GetOwner()->GetType(), _n1->collider->GetOwner()->GetType()) &&
				_n0->collider->Collides(_n1->collider) && 
				_n0->collider->GetOwner() != _n1->collider->GetOwner())
			{
				// 충돌하면 충돌쌍에 넣는다
				this->pairs.push_back(std::make_pair(_n0->collider, _n1->collider));
			}
		}
		// 1개만 리프인 경우
		else
		{
			// 리프가 아닌 노드의 자식에 대해 체크
			CrossChildren(_n1);

			// 각 노드의 AABB가 충돌하는지
			if (!_n0->aabb.IsCollision(_n1->aabb))
			{
				return;
			}

			// 충돌한다면 재귀적으로 계속 탐색
			ComputeCollisionPairs(_n0, _n1->children[0]);
			ComputeCollisionPairs(_n0, _n1->children[1]);
		}
	}
	// 한 노드가 리프 노드가 아니라면
	else
	{
		// 둘중 하나만 리프노드라면 ( 상동 )
		if (_n1->IsLeaf())
		{
			CrossChildren(_n0);
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			ComputeCollisionPairs(_n0->children[0], _n1);
			ComputeCollisionPairs(_n0->children[1], _n1);
		}
		// 둘 다 리프 노드가 아니라면
		else
		{
			// 각 노드의 자식 노드들을 전부 체크
			CrossChildren(_n0);
			CrossChildren(_n1);

			// 두 AABB가 충돌하는지
			if (!_n0->aabb.IsCollision(_n1->aabb))
			{
				return;
			}

			// 충돌한다면 자식에 대해서 전부 체크
			ComputeCollisionPairs(_n0->children[0], _n1->children[0]);
			ComputeCollisionPairs(_n0->children[0], _n1->children[1]);
			ComputeCollisionPairs(_n0->children[1], _n1->children[0]);
			ComputeCollisionPairs(_n0->children[1], _n1->children[1]);
		}
	}
}

/// <summary>
/// 해당 노드의 모든 자식에 대해 충돌 정보 초기화
/// </summary>
/// <param name="_node">최초 루프노드, 그후 노드</param>
void AABBTree::ClearChildrenCrossFlag(AABBNode* _node)
{
	// 검사 정보 초기화
	_node->crossedChildren = false;
	if (!_node->IsLeaf())
	{
		ClearChildrenCrossFlag(_node->children[0]);
		ClearChildrenCrossFlag(_node->children[1]);
	}
}

/// <summary>
/// 해당 노드의 모든 자식 노드에 대해 충돌 검사
/// </summary>
/// <param name="_node">노드</param>
void AABBTree::CrossChildren(AABBNode* _node)
{
	// 해당 노드의 자식에 대해서 충돌 검사
	// 이미 검사 한 노드라면 무시
	if (!_node->crossedChildren)
	{
		ComputeCollisionPairs(_node->children[0], _node->children[1]);
		_node->crossedChildren = true;
	}
}
