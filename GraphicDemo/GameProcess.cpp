#include "GameProcess.h"
#include <filesystem>


///���⼭ �ʱ�ȭ�� ���ٰŴ� �ΰ����
GameProcess::GameProcess() : grahicsEngine(nullptr), m_hWnd(nullptr)
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
	wchar_t  appName[] = L"�׷��� ���� ����";
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
		100, 100, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (!m_hWnd) return FALSE;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	grahicsEngine = new GraphicsEngine();
	grahicsEngine->Initialize(m_hWnd);

	grahicsEngine->LoadSpriteSheet("Image\\Sup_idle.png");
	grahicsEngine->LoadSpriteSheet("Image\\Deal_idle.png");

	//grahicsEngine->CreateEffects();
//// 	SoundManager::GetInstance()->SoundInit();

//// 
//// 	SoundManager::GetInstance()->MusicPlay(SoundManager::GetInstance()->EXAMPLE);
//
//	basePath = L"D:\\Document\\GA5th2Q_Project\\GA5th2Q_Project\\ChunSik\\4_Resources";
//	nowPath = std::filesystem::current_path();
//
//	relativePath = std::filesystem::relative(basePath, nowPath);
//
//	GetAllResources();
}

void GameProcess::Loop()
{
	HRESULT hr = grahicsEngine->LoadSpriteSheet("D:\\2qPro\\ChunSik\\4_Resources\\eft\\deal_skill_eft_ver2-Sheet.png");

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
		if (GetAsyncKeyState(VK_UP))
		{
			// SoundManager::GetInstance()->MusicStop();
		}
		///Render() : �׷��ȿ������� �׷��ٰ�
		grahicsEngine->BDraw();
		//grahicsEngine->ColorSet(D2D1::ColorF::Red);
		//grahicsEngine->DrawRectangle(10, 10, 20, 20);
		//grahicsEngine->DrawString(10, 10, "�ȳ��Ͻʴϱ�?�迹������");
		//grahicsEngine->DrawSprite("linakunSprites",0, 0, 0, 800, 600);
		//grahicsEngine->DrawSpriteAnimation("poketmonwalking", 1,4,3,4, 0, 0, 125, 130,100);
		///grahicsEngine->DrawSprite("effect", 0, 0, 0, 100, 100);
		grahicsEngine->SetEffect("a", 0.5f, 0, 0, 0);
		grahicsEngine->SetEffect("b", 0.5f, 1, 10,10);
		grahicsEngine->SetIsEffOn();
		//grahicsEngine->SetEffect(0.8);
		//grahicsEngine->Update();
		//DrawObj* draw = new DrawObj();
		//grahicsEngine->DrawSpriteAni("name", draw->Motions[0].motionSprites[0], 0, 0, 0, 100, 100);
		grahicsEngine->EDraw();
	}
}

void GameProcess::Finalize()
{
	///���⼭ �޸� �������̴ٰϴ� ���� �Ŵ��� �������������
	delete grahicsEngine;
}

std::wstring GameProcess::GetFilePath(std::filesystem::path _path)
{
	std::wstring temp = relativePath.wstring() + _path.wstring();
	return temp;
}

void GameProcess::GetAllResources()
{
	grahicsEngine->LoadSpriteSheet(GetFilePath(L"\\Example\\hellokitty-removebg-preview.png").c_str());
	grahicsEngine->LoadSpriteSheet(GetFilePath(L"\\Example\\image.bmp").c_str());
}
