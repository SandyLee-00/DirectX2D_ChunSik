#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"
SceneManager::SceneManager()
	: currentScene(nullptr)
	, collisionManager(nullptr)
{

}

SceneManager::~SceneManager()
{
	for(auto& s : this->scenes) 
	{
		delete s.second;
	}

	scenes.clear();
}

/// <summary>
/// 명시적 초기화
/// </summary>
/// <param name="_collisionManager">콜리젼 매니져</param>
void SceneManager::Initalize(CollisionManager* _collisionManager)
{
	this->collisionManager = _collisionManager;
}

/// <summary>
/// 현재 Scene 업데이트
/// </summary>
/// <param name="_dt">dt</param>
void SceneManager::Update(float _dt)
{
	currentScene->Update(_dt);
	currentScene->ComponentUpdate(_dt);
}

/// <summary>
/// 현재 씬 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void SceneManager::Render(GraphicsEngine* _graphicsEngine)
{
	currentScene->Render(_graphicsEngine);
}

/// <summary>
/// 현재 씬 디버깅정보 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void SceneManager::DebugRender(GraphicsEngine* _graphicsEngine)
{
	currentScene->DebugRender(_graphicsEngine);
}

/// <summary>
/// 현재 씬 최종 업데이트
/// </summary>
/// <param name="_dt">dt</param>
void SceneManager::FinalUpdate(float _dt)
{
	// currentScene->FinalUpdate(_dt);
}

/// <summary>
/// 씬 변경
/// </summary>
/// <param name="_name">변경 될 씬의 이름</param>
void SceneManager::ChangeScene(std::string _name)
{
	this->collisionManager->DestroyAABBTree();
	this->collisionManager->ResetCollison();
	// 만일 현재 씬이 있다면 나가는 함수 실행
	if (this->currentScene != nullptr) 
	{
		this->currentScene->Exit();
	}

	// 현재 씬을 바꿈
	this->currentScene = this->scenes[_name];
	// 바꾼 씬에 대해 진입 함수 실행
	this->currentScene->Enter();
}

/// <summary>
/// 씬 더하기
/// </summary>
/// <param name="_name">더할 씬의 이름</param>
/// <param name="_scene">씬</param>
void SceneManager::AddScene(std::string _name, Scene* _scene)
{
	assert(this->scenes.find(_name) == this->scenes.end() && "already exist scene name");
	this->scenes.insert({_name, _scene});
	if (this->currentScene == nullptr) 
	{
		this->currentScene = _scene;
		this->currentScene->Enter();
	}
}

/// <summary>
/// 오브젝트 더하기
/// </summary>
/// <param name="_object">더할 오브젝트</param>
void SceneManager::AddObject(Object* _object)
{
	this->currentScene->AddObject(_object);
}

void SceneManager::DeleteTypeObjects(OBJECT_TYPE _type)
{
	this->currentScene->DeleteTypeObjects(_type);
}
