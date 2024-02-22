#include "ManagerSet.h"


ManagerSet::ManagerSet()
{
	this->keyManager = new KeyManager();
	this->timeManager = new TimeManager();
	this->sceneManager = new SceneManager();
	this->collisionManager = new CollisionManager();
	this->pathManager = new PathManager();
	this->resourceManager = new ResourceManager();
}

ManagerSet::~ManagerSet()
{
	// �޸� �ʱ�ȭ
	delete this->collisionManager;
	delete this->sceneManager;
	delete this->timeManager;
	delete this->keyManager;
	delete this->pathManager;
	delete this->GetResourceManager();
}

/// <summary>
/// ��� �Ŵ��� ����� �ʱ�ȭ
/// </summary>
void ManagerSet::InitializeAllManager(HWND _hwnd, GraphicsEngine* _graphicsEngine)
{
	this->keyManager->Initalize(_hwnd);
	this->timeManager->Initalize();
	this->sceneManager->Initalize(this->collisionManager);
	this->collisionManager->Initalize(this->sceneManager);
	this->pathManager->Initalize();
	this->GetResourceManager()->Initalize(_graphicsEngine);
}

/// <summary>
/// ��� �Ŵ��� ������Ʈ
/// </summary>
void ManagerSet::Update()
{
	this->timeManager->Update();
	this->keyManager->Update();
	this->collisionManager->Update();
	this->sceneManager->Update(this->timeManager->GetfDT());
}

/// <summary>
/// ��� �Ŵ��� ����
/// �Ŵ��� �� ������ �ִ� �Ŵ����� ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void ManagerSet::Render(GraphicsEngine* _graphicsEngine)
{
	this->sceneManager->Render(_graphicsEngine);
}

/// <summary>
/// ��� �Ŵ��� ����� ���� ����
/// ����� ������ �ʿ��� �Ŵ����� ����
/// </summary>
/// <param name="_graphicsEngine">�׷��� ����</param>
void ManagerSet::DebugRender(GraphicsEngine* _graphicsEngine)
{
	this->sceneManager->DebugRender(_graphicsEngine);
	this->collisionManager->DebugRender(_graphicsEngine);
}

/// <summary>
/// ���� ������Ʈ
/// </summary>
void ManagerSet::FinalUpdate()
{
	this->sceneManager->FinalUpdate(this->timeManager->GetfDT());
}
