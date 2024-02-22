///
/// ���� ���� ��� �׽�Ʈ�� ���� ���� ������Ʈ
/// �ۼ��� : ����ȯ
/// ���� �ۼ��� : 2023/07/31
/// ���� �ۼ��� : 2023/07/31
/// 

#include "headers.h"
#include "GameProcess.h"
#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#define ID_EDIT 100
HWND gHWnd;
HINSTANCE gHInst;
HWND gHEdit;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ���α׷��� ���� ������(Entry Point). ��Ƽ����Ʈ ������Ʈ
int WINAPI wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR	lpCmdLine,
	_In_ int nCmdShow)
{
	// �޸� ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WCHAR szAppName[] = L"���� ���� ������ �ð��� ������!";
	MSG	msg;
	WNDCLASS wndclass{};

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

	RECT windowRect = { 0,0,100,100 };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	int titleBarHeight = abs(windowRect.top);

	int windowHeight = 1080;
	int windowWidth = 1920;

	// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	gHInst = hInstance;

	// ���� ����
	gHWnd = CreateWindowW(szAppName,
		szAppName,
		WS_POPUP,
		0, 0, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);

	if (!gHWnd) return FALSE;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(gHWnd, nCmdShow);
	UpdateWindow(gHWnd);

	// GameProcess ���� �� �ʱ�ȭ
	GameProcess* gameProcess = new GameProcess;
	gameProcess->Initialize(gHWnd);

	// �޽��� ����
	while (TRUE)
	{
		// �⺻ �޼��� ó��
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			// �̰� ������ �Է��� �޳�
			TranslateMessage(&msg);
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
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case ID_EDIT:
				switch (HIWORD(wParam))
				{
				case EN_CHANGE:
					SoundManager::GetInstance()->Play(SoundManager::SCENEEFFECT, SoundManager::SOUNDTYPING);
					gHEdit = GetWindow(hWnd, GW_CHILD);
					SetFocus(gHEdit);
					break;
				}
			}
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

