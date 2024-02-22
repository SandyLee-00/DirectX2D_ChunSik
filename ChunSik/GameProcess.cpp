#include "GameProcess.h"

///여기서 초기화를 해줄거다 두고봐라
GameProcess::GameProcess()
{
}

GameProcess::~GameProcess()
{
}

LRESULT GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
	wchar_t  appName[] = L"춘식이";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = GameProcess::WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = MAKEINTRESOURCEW(IDC_ARROW);
	wndclass.lpszClassName = appName;

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	// 윈도 생성 여기서 창 크기변경 나중에 변수로 뺄 것
	m_hWnd = CreateWindow(appName,
		appName,
		WS_OVERLAPPEDWINDOW,
		0, 0, 1920, 1080,
		NULL, NULL, hInstance, NULL);

	if (!m_hWnd) return FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
}

void GameProcess::Loop()
{
	// 메시지 루프
	while (true)
	{
		// 메세지 큐에 메세지가 있다면
		if (PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 메세지가 종료일떄 프로그램 종료
			if (m_Msg.message == WM_QUIT) break;

			// 처리되지 않은 메세지 -> OS가 알아서 처리
			else
			{
				DispatchMessage(&m_Msg);
			}
		}
		///Upate() :게임 컨텐츠를 무한루프
		///Render() : 그래픽엔진에서 그려줄것
	}
}

void GameProcess::Finalize()
{
	///여기서 메모리 삭제해줄겁니다 따로 매니저 만들수도있지만
}
