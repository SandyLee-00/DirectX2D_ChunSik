#pragma once
#include "headers.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

class KeyManager;
class CollisionManager;
class TimeManager;
class SceneManager;
class ObjectFactory;
class GraphicsEngine;
class PathManager;
class ResourceManager;

/// <summary>
/// 매니져 묶음 클래스
/// 
/// 최초 작성일 : 2023/07/26
/// 최초 작성일 : 2023/08/08
/// 작성자 : 김형환
/// 
/// 메니져 간의 초기화, 업데이트, 해제를 순서에 맞게 관리하기 위한 클래스
/// !!! 반드시 이 클래스를 이용해서 매니져 업데이트 할 것 반드시 !!!
/// !!! 게임 엔진 내 모든 업데이트는 이 클래스 통해서 이루어진다 !!!
/// !!! 메인 게임 루프에 이 클래스 Update 함수를 꼭 넣을 것     !!!
/// </summary>

class ManagerSet
{
private:
	KeyManager* keyManager;
	CollisionManager* collisionManager;
	TimeManager* timeManager;
	SceneManager* sceneManager;
	PathManager* pathManager;
	ResourceManager* resourceManager;
public:
	ManagerSet();
	virtual ~ManagerSet();

	// 순서에 맞도록 매니져 클래스들을 초기화, 업데이트
	void InitializeAllManager(HWND _hwnd, GraphicsEngine* _graphicsEngine);
	void Update();
	void Render(GraphicsEngine* _graphicsEngine);
	void DebugRender(GraphicsEngine* _graphicsEngine);
	void FinalUpdate();

	// 매니져 가져오기
	KeyManager* GetKeyManager() { return keyManager; }
	CollisionManager* GetCollisionManager() { return collisionManager; }
	TimeManager* GetTimeManager() { return timeManager; }
	SceneManager* GetSceneManager() { return sceneManager; }
	PathManager* GetPathManager() const { return pathManager; }
	ResourceManager* GetResourceManager() const { return resourceManager; }
};

