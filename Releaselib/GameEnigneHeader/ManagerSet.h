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
/// �Ŵ��� ���� Ŭ����
/// 
/// ���� �ۼ��� : 2023/07/26
/// ���� �ۼ��� : 2023/08/08
/// �ۼ��� : ����ȯ
/// 
/// �޴��� ���� �ʱ�ȭ, ������Ʈ, ������ ������ �°� �����ϱ� ���� Ŭ����
/// !!! �ݵ�� �� Ŭ������ �̿��ؼ� �Ŵ��� ������Ʈ �� �� �ݵ�� !!!
/// !!! ���� ���� �� ��� ������Ʈ�� �� Ŭ���� ���ؼ� �̷������ !!!
/// !!! ���� ���� ������ �� Ŭ���� Update �Լ��� �� ���� ��     !!!
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

	// ������ �µ��� �Ŵ��� Ŭ�������� �ʱ�ȭ, ������Ʈ
	void InitializeAllManager(HWND _hwnd, GraphicsEngine* _graphicsEngine);
	void Update();
	void Render(GraphicsEngine* _graphicsEngine);
	void DebugRender(GraphicsEngine* _graphicsEngine);
	void FinalUpdate();

	// �Ŵ��� ��������
	KeyManager* GetKeyManager() { return keyManager; }
	CollisionManager* GetCollisionManager() { return collisionManager; }
	TimeManager* GetTimeManager() { return timeManager; }
	SceneManager* GetSceneManager() { return sceneManager; }
	PathManager* GetPathManager() const { return pathManager; }
	ResourceManager* GetResourceManager() const { return resourceManager; }
};

