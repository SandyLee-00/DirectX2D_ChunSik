#include "TextLeftTime.h"

TextLeftTime::TextLeftTime(ManagerSet* _managers)
	: Object("TextLeftTime", _managers, OBJECT_TYPE::UI, { 0, 0 })
{
	isWorking = true;
	SetPlayleftSecond(MAX_PLAYTIME);
}

TextLeftTime::~TextLeftTime()
{

}

void TextLeftTime::Start()
{
	
}

void TextLeftTime::Update(float _deltaTime)
{
	if (isWorking == false)
	{
		return;
	}

	SetPlayleftSecond(GetPlayleftSecond() - _deltaTime);

	// 타이머 끝났을 때
	if(isWorking == false)
	{
		// 게임 종료
		SceneManager* sceneManager = this->GetManagers()->GetSceneManager();
		sceneManager->ChangeScene("RankingScene");
	}
}

void TextLeftTime::Render(GraphicsEngine* _graphicsEngine)
{
	float leftMinute = GetPlayleftSecond() / 60;
	float leftSecond = GetPlayleftSecond() - ((int)leftMinute * 60.f);

	_graphicsEngine->DrawSprite("timeBox", 68, 835, 10, 252, 95);

	std::string leftTime = std::to_string((int)leftMinute) + " : " + std::to_string((int)leftSecond);

	_graphicsEngine->ChangeFontSize(46.f);
	_graphicsEngine->ColorSet(D2D1::ColorF::White);
	_graphicsEngine->DrawString(906, 30, leftTime);
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(12.f);
}
