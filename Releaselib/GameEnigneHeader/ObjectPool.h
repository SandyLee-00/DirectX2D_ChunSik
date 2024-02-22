#pragma once
#include "headers.h"
#include "ManagerSet.h"

class ManagerSet;

/// <summary>
/// ������Ʈ Ŭ����
/// ���� �ۼ��� : 2023/08/13
/// ���� �ۼ��� : 2023/08/13
/// �ۼ��� : ����ȯ
/// 
/// ������Ʈ Ǯ Ŭ����
/// �̸� ������ ��ŭ�� ������Ʈ�� ���� �� �ξ��ٰ� �ʿ��� �� ���� ����
/// </summary>
/// <typeparam name="O">������Ʈ</typeparam>
/// <typeparam name="S">������</typeparam>
template <class O, size_t S>
class ObjectPool
{
private:
	std::queue<O*> objectPool;
	ManagerSet* manager;
public:
	ObjectPool(ManagerSet* _manager);
	virtual ~ObjectPool();

	O* GetObject();
	void ReleaseObject(O* _object);
};

template <class O, size_t S>
ObjectPool<O, S>::~ObjectPool()
{
	while (!this->objectPool.empty())
	{
		delete this->objectPool.front();
		this->objectPool.pop();
	}
}

template <class O, size_t S>
ObjectPool<O, S>::ObjectPool(ManagerSet* _manager)
	: manager(_manager)
{
	for (size_t i = 0; i < S; i++)
	{
		this->objectPool.push(new O(_manager));
	}
}

template <class O, size_t S>
O* ObjectPool<O, S>::GetObject()
{
	if (this->objectPool.empty())
	{
		this->objectPool.push(new O(this->manager));
	}
	O* result = this->objectPool.front();
	this->objectPool.pop();
	result->SetState(OBJECT_STATE::LIVE);
	return result;
}

template <class O, size_t S>
void ObjectPool<O, S>::ReleaseObject(O* _object)
{
	this->objectPool.push(_object);
}
