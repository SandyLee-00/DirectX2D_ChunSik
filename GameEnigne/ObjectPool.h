#pragma once
#include "headers.h"
#include "ManagerSet.h"

class ManagerSet;

/// <summary>
/// 오브젝트 클래스
/// 최초 작성일 : 2023/08/13
/// 최초 작성일 : 2023/08/13
/// 작성자 : 김형환
/// 
/// 오브젝트 풀 클래스
/// 미리 정해진 만큼의 오브젝트를 저장 해 두었다가 필요할 때 꺼내 쓰기
/// </summary>
/// <typeparam name="O">오브젝트</typeparam>
/// <typeparam name="S">사이즈</typeparam>
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
