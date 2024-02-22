#include "GameProcess.h"

///���⼭ �ʱ�ȭ�� ���ٰŴ� �ΰ����
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
	wchar_t  appName[] = L"�����";
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

	// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	// ���� ���� ���⼭ â ũ�⺯�� ���߿� ������ �� ��
	m_hWnd = CreateWindow(appName,
		appName,
		WS_OVERLAPPEDWINDOW,
		0, 0, 1920, 1080,
		NULL, NULL, hInstance, NULL);

	if (!m_hWnd) return FALSE;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
}

void GameProcess::Loop()
{
	// �޽��� ����
	while (true)
	{
		// �޼��� ť�� �޼����� �ִٸ�
		if (PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE))
		{
			// �޼����� �����ϋ� ���α׷� ����
			if (m_Msg.message == WM_QUIT) break;

			// ó������ ���� �޼��� -> OS�� �˾Ƽ� ó��
			else
			{
				DispatchMessage(&m_Msg);
			}
		}
		///Upate() :���� �������� ���ѷ���
		///Render() : �׷��ȿ������� �׷��ٰ�
	}
}

void GameProcess::Finalize()
{
	///���⼭ �޸� �������̴ٰϴ� ���� �Ŵ��� �������������
}
