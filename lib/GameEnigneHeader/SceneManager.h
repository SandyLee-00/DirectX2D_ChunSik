#pragma once
#include "headers.h"

class Scene;
class CollisionManager;
class Object;
class GraphicsEngine;

/// <summary>
/// SceneManager 클래스
/// 최초 작성일 : 2023/07/25
/// 최초 작성일 : 2023/07/31
/// 작성자 : 김형환
/// 
/// Scene을 관리해주는 클래스
/// </summary>

class SceneManager
{
private:
	Scene* currentScene;
	std::map<std::string, Scene*> scenes;
	CollisionManager* collisionManager;

public:
	SceneManager();
	~SceneManager();

	void Initalize(CollisionManager* _collisionManager);

	void Update(float _dt);
	void Render(GraphicsEngine* _graphicsEngine);
	void DebugRender(GraphicsEngine* _graphicsEngine);
	void FinalUpdate(float _dt);

	void ChangeScene(std::string _name);
	void AddScene(std::string _name, Scene* _scene);
	void AddObject(Object* _object);

	Scene* GetCurrentScene() const { return currentScene; }
	void SetCurrentScene(Scene* val) { currentScene = val; }

	void DeleteTypeObjects(OBJECT_TYPE _type);
};

