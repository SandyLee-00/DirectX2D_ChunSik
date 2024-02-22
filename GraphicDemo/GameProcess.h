/// <summary>
/// �������μ���
/// ���ӿ����� ������ ���
/// 7.20 lina
/// </summary>
#pragma once
#include <windows.h>
#include "GraphicsEngine.h"
#include "SoundManager.h"
class GameProcess
{
	HWND m_hWnd;
	MSG m_Msg;
	GraphicsEngine* grahicsEngine;
	/// 27�ϳ� �߰��� �� ���� �� ������ �����Ŵ�
	//To do : exobj,DrawObj ,PathManager �����Ұ� �����ߴµ� �ڲ� ����� �ù�����

	///���� ��� �б�
	std::filesystem::path basePath; //���� ã�� ���
	std::filesystem::path nowPath; //������
	std::filesystem::path relativePath; //����θ� ���ߴ�!!
public:
	GameProcess();
	~GameProcess();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HRESULT Initialize(HINSTANCE hInstance);
	void Loop();
	void Finalize();

	//�̹����� �ҷ����� ����
	std::wstring GetFilePath(std::filesystem::path _path);
	void GetAllResources();
};
