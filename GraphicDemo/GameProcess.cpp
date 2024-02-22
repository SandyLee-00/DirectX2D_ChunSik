#include "GameProcess.h"
#include <filesystem>


///여기서 초기화를 해줄거다 두고봐라
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
	wchar_t  appName[] = L"그래픽 엔진 데모";
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
		100, 100, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (!m_hWnd) return FALSE;

	// 생성된 윈도를 화면에 표시
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
		if (GetAsyncKeyState(VK_UP))
		{
			// SoundManager::GetInstance()->MusicStop();
		}
		///Render() : 그래픽엔진에서 그려줄것
		grahicsEngine->BDraw();
		//grahicsEngine->ColorSet(D2D1::ColorF::Red);
		//grahicsEngine->DrawRectangle(10, 10, 20, 20);
		//grahicsEngine->DrawString(10, 10, "안녕하십니까?김예리나다");
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
	///여기서 메모리 삭제해줄겁니다 따로 매니저 만들수도있지만
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
