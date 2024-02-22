#pragma once
#include "headers.h"
	
class QuadNode;

class QuadTree
{
private:
	Vector2 minPoint;
	Vector2 maxPoint;
	int depth;
	QuadNode* root;

public:
	QuadTree(Vector2 _minPoint, Vector2 _maxPoint, int _depth);
	~QuadTree();
};

