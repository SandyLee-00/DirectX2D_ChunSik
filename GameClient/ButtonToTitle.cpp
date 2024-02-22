#include "ButtonToTitle.h"

ButtonToTitle::ButtonToTitle(ManagerSet* _managers)
	: Button(_managers)
{

}

ButtonToTitle::~ButtonToTitle()
{

}

void ButtonToTitle::Render(GraphicsEngine* _graphicsEngine)
{
	// 여기에 버튼 이미지 넣기
	_graphicsEngine->DrawSprite("gototitlebtn", 99, 1680, 960, 215, 77);

	// 글자색 / 글자 크기 / 글자 위치 설정
	// Button에서 protected로 text / position / size를 받아옴
	std::string renderText = text;
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(fontSize);
	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
	_graphicsEngine->ChangeFontSize(12.f);
}

void ButtonToTitle::OnButtonClicked()
{
	SoundManager::GetInstance()->Play(SoundManager::MOUSEEFFECT, SoundManager::BUTTON);
	GetManagers()->GetSceneManager()->ChangeScene("TitleScene");
}