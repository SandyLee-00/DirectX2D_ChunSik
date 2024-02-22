#include "BackGroundObject.h"

BackGroundObject::BackGroundObject(ManagerSet* _managers)
	: Object("BackGroundObject", _managers, OBJECT_TYPE::BACK_GROUND, (0.f, 0.f))
{
	currentPage = 0;
	maxPage = 0;
}

BackGroundObject::~BackGroundObject()
{

}

void BackGroundObject::Start()
{

}

void BackGroundObject::Update(float _deltaTime)
{
	KeyManager* keyManager = this->GetManagers()->GetKeyManager();

	if(keyManager->GetKeyState(KEY::LEFT) == KEY_STATE::DOWN)
	{
		currentPage--;
	}
	else if (keyManager->GetKeyState(KEY::RIGHT) == KEY_STATE::DOWN)
	{
		currentPage++;
	}

	// 0페이지인데 이전 페이지 누르면 0페이지 유지
	if (currentPage < 0)
	{
		currentPage = 0;
	}

	// 최대 페이지인데 다음 페이지 누르면 TutorialScene 씬으로 넘어가기
	if (currentPage >= maxPage && this->GetName() == "OpeningScene")
	{
		this->GetManagers()->GetSceneManager()->ChangeScene("TutorialScene");
		currentPage = 0;
	}
	// 최대 페이지인데 다음 페이지 누르면 MainGameScene 씬으로 넘어가기
	else if (currentPage >= maxPage && this->GetName() == "TutorialScene")
	{
		this->GetManagers()->GetSceneManager()->ChangeScene("MainGameScene");
		currentPage = 0;
	}
}

void BackGroundObject::FinalUpdate(float _deltaTime)
{

}

// 전체 화면 배경 그리기 전부 여기에 넣기
void BackGroundObject::Render(GraphicsEngine* _graphicsEngine)
{

	if (this->GetName() == "TitleScene")
	{
		// 타이틀 화면 배경 그리기
		_graphicsEngine->DrawSprite("title", 94, 0, 0, 1920, 1080);
	}
	// 오프닝 컷신 3개
	else if (this->GetName() == "OpeningScene")
	{
		if (currentPage <= 0)
		{
			// OpeningScene 첫번째 배경 그리기
			_graphicsEngine->DrawSprite("opening1", 73, 0, 0, 1920, 1080);
		}

		else if (currentPage == 1)
		{
			// OpeningScene 두번째 배경 그리기
			_graphicsEngine->DrawSprite("opening2", 74, 0, 0, 1920, 1080);
		}

		else if (currentPage >= 2)
		{
			// OpeningScene 세번째 배경 그리기
			_graphicsEngine->DrawSprite("opening3", 75, 0, 0, 1920, 1080);
		}
	}

	// 튜토리얼 페이지 7개
	else if (this->GetName() == "TutorialScene")
	{
		if (currentPage <= 0)
		{
			// TutorialScene 첫번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial1", 87, 0, 0, 1920, 1080);
		}
		else if (currentPage == 1)
		{
			// TutorialScene 두번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial2", 88, 0, 0, 1920, 1080);
		}
		else if (currentPage == 2)
		{
			// TutorialScene 세번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial3", 89, 0, 0, 1920, 1080);
		}
		else if (currentPage == 3)
		{
			// TutorialScene 네번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial4", 90, 0, 0, 1920, 1080);
		}
		else if (currentPage == 4)
		{
			// TutorialScene 다섯번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial5", 91, 0, 0, 1920, 1080);
		}
		else if (currentPage == 5)
		{
			// TutorialScene 여섯번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial6", 92, 0, 0, 1920, 1080);
		}
		else if (currentPage >= 6)
		{
			// TutorialScene 일곱번째 배경 그리기
			_graphicsEngine->DrawSprite("tutorial7", 93, 0, 0, 1920, 1080);
		}

	}
	else if (this->GetName() == "MainGameScene")
	{
		_graphicsEngine->DrawSprite("bg", 5, 0, 0, 1920, 1080);

		_graphicsEngine->DrawSprite("bgtree", 6, 0, 0, 1920, 1080);


	}
	else if (this->GetName() == "RankingScene")
	{
		_graphicsEngine->DrawSprite("dummy", 25, 0, 0, 1920, 1080);
	}
	else if (this->GetName() == "CreditScene")
	{
		// 크레딧 씬 배경 그리기
		_graphicsEngine->DrawSprite("credit", 100, 0, 0, 1920, 1080);
	}


}

void BackGroundObject::DebugRender(GraphicsEngine* _graphicsEngine)
{

	TimeManager* tm = this->GetManagers()->GetTimeManager();

	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	// 글자 크기 키우기
	_graphicsEngine->ChangeFontSize(30.f);

	std::string printString = "";
	printString += "currentPage : " + std::to_string(currentPage) + "\n";
	printString += "maxPage : " + std::to_string(maxPage) + "\n";

	// 프레임 디버깅용
	printString += "FPS : " + std::to_string((int)(1.f / tm->GetfDT())) + "\n";

	// 디버깅용으로 빈 오브젝트 글자 출력해주기
	_graphicsEngine->DrawString(0, 0, printString + "_DEBUG");

	// 글자 크기 되돌리기
	_graphicsEngine->ChangeFontSize(12.f);

}
