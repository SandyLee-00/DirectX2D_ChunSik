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
/// ����� �ʱ�ȭ
/// </summary>
/// <param name="_collisionManager">�ݸ��� �Ŵ���</param>
void SceneManager::Initalize(CollisionManager* _collisionManager)
{
	this->collisionManager = _collisionManager;
}

/// <summary>
/// ���� Scene ������Ʈ
/// </summary>
/// <param name="_dt">dt</param>
void SceneManager::Update(float _dt)
{
	currentScene->Update(_dt);
	currentScene->ComponentUpdate(_dt);
}

/// <summary>
/// ���� �� ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void SceneManager::Render(GraphicsEngine* _graphicsEngine)
{
	currentScene->Render(_graphicsEngine);
}

/// <summary>
/// ���� �� ��������� ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void SceneManager::DebugRender(GraphicsEngine* _graphicsEngine)
{
	currentScene->DebugRender(_graphicsEngine);
}

/// <summary>
/// ���� �� ���� ������Ʈ
/// </summary>
/// <param name="_dt">dt</param>
void SceneManager::FinalUpdate(float _dt)
{
	// currentScene->FinalUpdate(_dt);
}

/// <summary>
/// �� ����
/// </summary>
/// <param name="_name">���� �� ���� �̸�</param>
void SceneManager::ChangeScene(std::string _name)
{
	this->collisionManager->DestroyAABBTree();
	this->collisionManager->ResetCollison();
	// ���� ���� ���� �ִٸ� ������ �Լ� ����
	if (this->currentScene != nullptr) 
	{
		this->currentScene->Exit();
	}

	// ���� ���� �ٲ�
	this->currentScene = this->scenes[_name];
	// �ٲ� ���� ���� ���� �Լ� ����
	this->currentScene->Enter();
}

/// <summary>
/// �� ���ϱ�
/// </summary>
/// <param name="_name">���� ���� �̸�</param>
/// <param name="_scene">��</param>
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
/// ������Ʈ ���ϱ�
/// </summary>
/// <param name="_object">���� ������Ʈ</param>
void SceneManager::AddObject(Object* _object)
{
	this->currentScene->AddObject(_object);
}

void SceneManager::DeleteTypeObjects(OBJECT_TYPE _type)
{
	this->currentScene->DeleteTypeObjects(_type);
}
