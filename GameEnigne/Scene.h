#pragma once
#include "headers.h"

class Object;
class ManagerSet;
class GraphicsEngine;
/// <summary>
/// Scene Ŭ����
/// ���� �ۼ��� : 2023/07/25
/// ���� �ۼ��� : 2023/08/01
/// �ۼ��� : ����ȯ
/// 
/// Scene Ŭ����
/// Object�� ��ġ�ǰ� ���ư��� Ŭ����
/// https://docs.unity3d.com/Manual/ExecutionOrder.html
/// </summary>

class Scene
{
protected:
	std::vector<std::list<Object*>> objects;
	ManagerSet* managers;
	bool isPause;
	bool scenePause;

public:
	Scene(ManagerSet* _managers);
	virtual ~Scene();

	virtual void Update(float _dt);
	virtual void ComponentUpdate(float _dt);
	virtual void FinalUpdate(float _dt);

	virtual void Render(GraphicsEngine* _graphicsEngine);
	virtual void DebugRender(GraphicsEngine* _graphicsEngine);

	virtual void Enter() abstract;
	virtual void Exit() abstract;

	void AddObject(Object* _object);
	void DeleteAllObjects();
	void DeleteTypeObjects(OBJECT_TYPE _type);

	std::list<Object*>& GetObjectListType(int _type);

	bool GetIsPause() const { return isPause; }
	void SetIsPause(bool val) { isPause = val; }
	bool GetScenePause() const { return scenePause; }
	void SetScenePause(bool val) { scenePause = val; }
};

