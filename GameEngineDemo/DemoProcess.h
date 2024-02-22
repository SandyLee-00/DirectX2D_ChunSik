#pragma once
#include <windows.h>
#include "GraphicsEngine.h"
#include "ManagerSet.h"



/// <summry>
/// ���� ���� �� ������� �ϱ� ���� Ŭ����
/// ���� �ۼ��� : 2023/07/31
/// ���� �ۼ��� : 2023/07/31
/// �ۼ��� : ����ȯ
/// <\summry>


class DemoProcess
{
private:
	// ������ �ڵ鷯
	HWND hwnd;
	GraphicsEngine* graphicsEngine;
	ManagerSet* manager;

public:
	// ������ �Ҹ���
	DemoProcess();
	~DemoProcess();

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

