#pragma once
#include "headers.h"

class Collider;

class QuadNode
{
private:
	Vector2 minPoint;
	Vector2 maxPoint;
	QuadNode* parent = nullptr;
	std::vector<Collider*> colliders;
	QuadNode* child[4];
	bool isLeaf;
	int objectCount;

public:
	QuadNode(Vector2 _min, Vector2 _max, QuadNode* _parent);
	~QuadNode();

	void InsertCollider(Collider* _collider);
};

