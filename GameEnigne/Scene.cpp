#include "Scene.h"
#include "Object.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "ManagerSet.h"
Scene::Scene(ManagerSet* _managers)
	: managers(_managers)
	, objects(std::vector<std::list<Object*>>((int)(OBJECT_TYPE::END)))
	, isPause(false)
	, scenePause(false)
{

}

Scene::~Scene()
{
	DeleteAllObjects();
	this->objects.clear();
}

/// <summary>
/// 씬에 있는 모든 오브젝트 업데이트
/// </summary>
/// <param name="_dt">시간</param>
void Scene::Update(float _dt)
{
	if (this->scenePause) 
	{
		return;
	}
	for (int i = 0; i < (int)(OBJECT_TYPE::END); i++)
	{
		auto obj = this->objects[i].begin();
		while (obj != this->objects[i].end() && this->objects[i].size() != 0)
		{
			if ((*obj)->GetState() != OBJECT_STATE::DEAD)
			{
				if (!(this->isPause && (*obj)->GetCanPause()))
				{
					(*obj)->Update(_dt);
				}
				obj++;
			}
			else
			{
				obj = this->objects[i].erase(obj);
			}
		}
	}
}

/// <summary>
/// 씬에 있는 모든 오브젝트 업데이트
/// </summary>
/// <param name="_dt">시간</param>
void Scene::ComponentUpdate(float _dt)
{
	if (this->scenePause)
	{
		return;
	}
	for (int i = 0; i < (int)(OBJECT_TYPE::END); i++)
	{
		if (this->isPause)
		{
			continue;
		}
		auto obj = this->objects[i].begin();
		while (obj != this->objects[i].end() && this->objects[i].size() != 0)
		{
			if ((*obj)->IsAlive())
			{
				if (!(this->isPause && (*obj)->GetCanPause()))
				{
					(*obj)->ComponentUpdate(_dt);
				}
				obj++;
			}
			else
			{
				obj = this->objects[i].erase(obj);
			}
		}
	}
}

/// <summary>
/// 씬에 있는 모든 오브젝트 업데이트
/// </summary>
/// <param name="_dt">시간</param>
void Scene::FinalUpdate(float _dt)
{
	if (this->scenePause)
	{
		return;
	}
	for (auto& objectList : this->objects)
	{
		auto obj = objectList.begin();
		while (obj != objectList.end() && objectList.size() != 0)
		{
			if ((*obj)->IsAlive())
			{
				if (!(this->isPause && (*obj)->GetCanPause()))
				{
					(*obj)->FinalUpdate(_dt);
				}
				obj++;
			}
			obj++;
		}
	}
}

/// <summary>
/// 씬에 있는 모든 오브젝트 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void Scene::Render(GraphicsEngine* _graphicsEngine)
{
	for (auto& objectList : this->objects)
	{
		auto obj = objectList.begin();
		while (obj != objectList.end() && objectList.size() != 0)
		{
			if ((*obj)->IsAlive())
			{
				(*obj)->Render(_graphicsEngine);
				(*obj)->ComponentRender(_graphicsEngine);
			}
			obj++;
		}
	}
}

/// <summary>
/// 씬에 있는 모든 오브젝트의 디버깅 정보 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void Scene::DebugRender(GraphicsEngine* _graphicsEngine)
{
	for (auto& objectList : this->objects)
	{
		auto obj = objectList.begin();
		while (obj != objectList.end() && objectList.size() != 0)
		{
			if ((*obj)->IsAlive())
			{
				(*obj)->DebugRender(_graphicsEngine);
				obj++;
			}
		}
	}
}

/// <summary>
/// 오브젝트 추가
/// </summary>
/// <param name="_object">추가 될 오브젝트</param>
void Scene::AddObject(Object* _object)
{
	// 씬에 추가
	this->objects[(int)(_object->GetType())].push_back(_object);
	_object->Start();
}

void Scene::DeleteAllObjects()
{
	for (auto& objectList : this->objects)
	{
		for (auto obj : objectList)
		{
			delete obj;
		}
	}


	for (auto& objectList : this->objects)
	{
		objectList.clear();
	}
}

void Scene::DeleteTypeObjects(OBJECT_TYPE _type)
{
	for (auto object : this->objects[(int)(_type)])
	{
		delete object;
	}
	this->objects[(int)(_type)].clear();
	this->objects[(int)(_type)] = std::list<Object*>();
}

std::list<Object*>& Scene::GetObjectListType(int _type)
{
	return this->objects[_type];
}
