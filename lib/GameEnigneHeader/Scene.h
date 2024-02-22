#pragma once
#include "headers.h"

class Object;
class ManagerSet;
class GraphicsEngine;
/// <summary>
/// Scene 클래스
/// 최초 작성일 : 2023/07/25
/// 최초 작성일 : 2023/08/01
/// 작성자 : 김형환
/// 
/// Scene 클래스
/// Object가 배치되고 돌아가는 클래스
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

