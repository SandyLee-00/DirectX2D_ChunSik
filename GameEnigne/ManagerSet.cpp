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
	// 메모리 초기화
	delete this->collisionManager;
	delete this->sceneManager;
	delete this->timeManager;
	delete this->keyManager;
	delete this->pathManager;
	delete this->GetResourceManager();
}

/// <summary>
/// 모든 매니져 명시적 초기화
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
/// 모든 매니져 업데이트
/// </summary>
void ManagerSet::Update()
{
	this->timeManager->Update();
	this->keyManager->Update();
	this->collisionManager->Update();
	this->sceneManager->Update(this->timeManager->GetfDT());
}

/// <summary>
/// 모든 매니져 렌더
/// 매니져 중 렌더가 있는 매니져만 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void ManagerSet::Render(GraphicsEngine* _graphicsEngine)
{
	this->sceneManager->Render(_graphicsEngine);
}

/// <summary>
/// 모든 매니져 디버깅 정보 렌더
/// 디버깅 렌더가 필요한 매니져만 렌더
/// </summary>
/// <param name="_graphicsEngine">그래픽 엔진</param>
void ManagerSet::DebugRender(GraphicsEngine* _graphicsEngine)
{
	this->sceneManager->DebugRender(_graphicsEngine);
	this->collisionManager->DebugRender(_graphicsEngine);
}

/// <summary>
/// 최종 업데이트
/// </summary>
void ManagerSet::FinalUpdate()
{
	this->sceneManager->FinalUpdate(this->timeManager->GetfDT());
}
