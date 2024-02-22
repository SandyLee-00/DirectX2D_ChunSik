#pragma once
#include "GraphicsEngine.h"
#include "ManagerSet.h"
#include <windows.h>
#include "SoundManager.h"


/// <summry>
/// ���� ���� �� ������� �ϱ� ���� Ŭ����
/// ���� �ۼ��� : 2023/07/31
/// ���� �ۼ��� : 2023/07/31
/// �ۼ��� : ����ȯ
/// <\summry>


class GameProcess
{
private:
	// ������ �ڵ鷯
	HWND hwnd;
	GraphicsEngine* graphicsEngine;
	ManagerSet* manager;
	bool isDebug;

public:
	// ������ �Ҹ���
	GameProcess();
	~GameProcess();

	// ����� �ʱ�ȭ
	void Initialize(HWND _hwnd);

	// �������� ����Ǵ� �Լ�
	void Process();
private:
	// ���� ����Ǵ� �Լ�
	void Update();
	void Render();
	void FinalUpdate();

};

