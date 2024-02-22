#pragma once
#include "headers.h"
#include "AABB.h"

class Collider;

/// <summary>
/// AABB Ʈ�� ��� Ŭ����
/// ���� �ۼ��� : 2023/08/07
/// ���� �ۼ��� : 2023/08/08
/// �ۼ��� : ����ȯ
/// 
/// AABB Tree ������ ���� ��� Ŭ����
/// ��� Ư�� �� ��� ���� ����
/// <\summry>

class AABBNode
{
public:
	AABBNode* parent;
	AABBNode* children[2];
	bool crossedChildren;
	AABB aabb;
	Collider* collider;

public:
	AABBNode();
	~AABBNode();

	bool IsLeaf() { return children[0] == nullptr; }
	void AddChild(AABBNode* _a, AABBNode* _b);
	void SetLeaf(Collider* _collider);
	void Update(float _margine);
	AABBNode* GetSibling();
};

