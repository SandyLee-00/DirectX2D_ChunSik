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
	// ���⿡ ��ư �̹��� �ֱ�
	_graphicsEngine->DrawSprite("gototitlebtn", 99, 1680, 960, 215, 77);

	// ���ڻ� / ���� ũ�� / ���� ��ġ ����
	// Button���� protected�� text / position / size�� �޾ƿ�
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