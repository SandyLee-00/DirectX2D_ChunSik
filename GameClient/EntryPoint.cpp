///
/// 게임 엔진 기능 테스트를 위한 데모 프로젝트
/// 작성자 : 김형환
/// 최초 작성일 : 2023/07/31
/// 최종 작성일 : 2023/07/31
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

// 프로그램의 최초 진입점(Entry Point). 멀티바이트 프로젝트
int WINAPI wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR	lpCmdLine,
	_In_ int nCmdShow)
{
	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WCHAR szAppName[] = L"잠을 깨기 전까지 시간을 벌어줘!";
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

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	gHInst = hInstance;

	// 윈도 생성
	gHWnd = CreateWindowW(szAppName,
		szAppName,
		WS_POPUP,
		0, 0, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);

	if (!gHWnd) return FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(gHWnd, nCmdShow);
	UpdateWindow(gHWnd);

	// GameProcess 생성 및 초기화
	GameProcess* gameProcess = new GameProcess;
	gameProcess->Initialize(gHWnd);

	// 메시지 루프
	while (TRUE)
	{
		// 기본 메세지 처리
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			// 이거 있으면 입력은 받네
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 엔진 동작
			gameProcess->Process();
		}
	}

	// 프로그램 종료 전 엔진 반환
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

