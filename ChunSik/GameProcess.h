/// <summary>
/// �������μ���
/// ������ ������ ���
/// 7.20 lina
/// </summary>
#pragma once
#include <windows.h>
class GameProcess
{
	HWND m_hWnd;
	MSG m_Msg;
public:
	GameProcess();
	~GameProcess();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HRESULT Initialize(HINSTANCE hInstance);
	void Loop();
	void Finalize();


};

