#include "CollisionManager.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "AABBtree.h"

CollisionManager::CollisionManager()
	: checkMap{ 0, }
{

}

CollisionManager::~CollisionManager()
{
	delete aabbTree;
	for(auto& collision : this->collisions) 
	{
		delete collision.second;
	}
}

/// <summary>
/// ����� �ʱ�ȭ
/// </summary>
/// <param name="_sceneManger">�� �Ŵ���</param>
void CollisionManager::Initalize(SceneManager* _sceneManger)
{
	this->sceneManger = _sceneManger;
	this->aabbTree = new AABBTree(0.0f, this);
}

/// <summary>
/// �ݶ��̴� �߰�
/// </summary>
/// <param name="_input">�߰��� �ݶ��̴�</param>
void CollisionManager::AddCollider(Collider* _input)
{
	this->aabbTree->AddCollider(_input);
}

/// <summary>
/// �浹 ������Ʈ
/// </summary>
void CollisionManager::Update()
{
	this->aabbTree->Update();

	std::list<std::pair<Collider*, Collider*>> pairs = this->aabbTree->GetCollisionPairs();

	SolveCollision(pairs);
}

/// <summary>
/// ����� ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void CollisionManager::DebugRender(GraphicsEngine* _graphicsEngine)
{
	this->aabbTree->DebugRender(_graphicsEngine);
}

/// <summary>
/// �浹 �� ������Ʈ
/// </summary>
void CollisionManager::CheckCollisionMap()
{
	
}

/// <summary>
/// �浹 ������Ʈ
/// </summary>
void CollisionManager::UpdateCollision()
{
	// ��� �浹�� ���Ͽ�
	for(auto& c : this->collisions) 
	{
		// �浹ü ��������
		Collision* collision = c.second;
		Collider* a = collision->collider1;
		Collider* b = collision->collider2;

		// b �浹ü�� ������ ������� ���̳��� ĳ����
		CircleCollider* cir = dynamic_cast<CircleCollider*>(b);
		BoxCollider* box = dynamic_cast<BoxCollider*>(b);

		// ĳ���� ����� �浹 ���θ� �ľ�
		if ((cir != nullptr && a->IsCollision(cir)) || 
			(box != nullptr && a->IsCollision(box))) 
		{
			// �浹��
			collision->isCollisionNow = true;
		}
		else
		{
			// �浹���� ����
			collision->isCollisionNow = false;
		}
	}
}

/// <summary>
/// �浹 �ذ�
/// </summary>
void CollisionManager::SolveCollision(std::list<std::pair<Collider*, Collider*>> _pairs)
{
	// ��� �浹�� ����
	for(auto& p : _pairs)
	{
		// �浹 ������
		COLLIDER_KEY key = COLLIDER_KEY(p.first, p.second);
		std::map<COLLIDER_KEY, Collision*>::iterator collisionInfo = collisions.find(key);

		if (collisionInfo == collisions.end())
		{
			collisions.insert({ key, new Collision(p.first, p.second) });
		}
		else
		{
			collisionInfo->second->isCollisionNow = true;
		}	
	}

	for(auto& c : collisions) 
	{
		Collision* collision = c.second;

		// ���� ������ ���� �� �� �浹���� �ʾ����� ����
		if (!(collision->isCollisionNow || collision->isCollisionPast))
		{
			continue;
		}
		// ������ �浹�߰� ���ݵ� �浹�� (stay)
		else if (collision->isCollisionNow && collision->isCollisionPast)
		{
			collision->collider1->GetOwner()->OnCollisionStay(collision->collider2->GetOwner());
			collision->collider2->GetOwner()->OnCollisionStay(collision->collider1->GetOwner());
		}
		// ������ �浹 ���� �ʾҰ� ������ �� (enter)
		else if (collision->isCollisionNow == true && collision->isCollisionPast == false)
		{
			collision->collider1->GetOwner()->OnCollisionEnter(collision->collider2->GetOwner());
			collision->collider2->GetOwner()->OnCollisionEnter(collision->collider1->GetOwner());
		}
		// ������ �浹 �߰� ������ �ƴ� (ecit)
		else if (collision->isCollisionNow == false && collision->isCollisionPast == true)
		{
			collision->collider1->GetOwner()->OnCollisionExit(collision->collider2->GetOwner());
			collision->collider2->GetOwner()->OnCollisionExit(collision->collider1->GetOwner());
		}
		// �浹 ����ȭ
		collision->isCollisionPast = collision->isCollisionNow;
		collision->isCollisionNow = false;
	}
}

/// <summary>
/// ��Ʈ �÷��׸� �̿��� �浹 ����
/// </summary>
/// <param name="_a">������Ʈ Ÿ��</param>
/// <param name="_b">������Ʈ Ÿ��</param>
void CollisionManager::MarkCollisionType(OBJECT_TYPE _a, OBJECT_TYPE _b)
{
	// ��Ʈ �÷��� ����
	this->checkMap[(int)_a] |= 1 << (int)_b;
	this->checkMap[(int)_b] |= 1 << (int)_a;
}

/// <summary>
/// �ѵ� ������ Ÿ������
/// </summary>
/// <param name="_a">Ÿ�� 1</param>
/// <param name="_b">Ÿ�� 2</param>
/// <returns>�浹 ���� ����</returns>
bool CollisionManager::CheckType(OBJECT_TYPE _a, OBJECT_TYPE _b)
{
	return this->checkMap[(int)_a] & 1 << (int)_b;
}

/// <summary>
/// ��� �浹 ���� 0 ���� ����
/// </summary>
void CollisionManager::ResetCollisoinType()
{
	for (int i = 0; i < (int)OBJECT_TYPE::END; i++)
	{
		this->checkMap[i] = 0;
	}
}

void CollisionManager::ResetCollison()
{
	for (auto& collision : this->collisions)
	{
		delete collision.second;
	}
	collisions.clear();
	collisions = std::map<COLLIDER_KEY, Collision*>();
}

void CollisionManager::DestroyAABBTree()
{
	this->aabbTree->Clear();
}
