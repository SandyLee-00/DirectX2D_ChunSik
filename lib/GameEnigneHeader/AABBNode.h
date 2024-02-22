#pragma once
#include "headers.h"
#include "AABB.h"

class Collider;

/// <summary>
/// AABB 트리 노드 클래스
/// 최초 작성일 : 2023/08/07
/// 최초 작성일 : 2023/08/08
/// 작성자 : 김형환
/// 
/// AABB Tree 구현을 위한 노드 클래스
/// 노드 특성 상 모든 정보 공개
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

