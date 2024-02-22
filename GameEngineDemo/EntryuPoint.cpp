///
/// ���� ���� ��� �׽�Ʈ�� ���� ���� ������Ʈ
/// �ۼ��� : ����ȯ
/// ���� �ۼ��� : 2023/07/31
/// ���� �ۼ��� : 2023/07/31
/// 

#include <windows.h>
#include "DemoProcess.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ���α׷��� ���� ������(Entry Point). ��Ƽ����Ʈ ������Ʈ
int WINAPI wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR	lpCmdLine,
	_In_ int nCmdShow)
{
	// _CrtSetBreakAlloc(493);


	
	WCHAR szAppName[] = L"Chunsik Engine Deom";
	HWND hWnd;
	MSG	msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	// ���� ����
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, 1280, 720,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// GameProcess ���� �� �ʱ�ȭ
	DemoProcess* gameProcess = new DemoProcess;
	gameProcess->Initialize(hWnd);
	// �޽��� ����
	while (TRUE)
	{
		// �⺻ �޼��� ó��
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);

		}
		else
		{
			// ���� ����
			gameProcess->Process();
		}
	}

	// ���α׷� ���� �� ���� ��ȯ
	delete gameProcess;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

