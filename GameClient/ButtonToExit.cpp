#include "ButtonToExit.h"

extern HWND gHWnd;

ButtonToExit::ButtonToExit(ManagerSet* _managers)
	: Button(_managers)
{

}

ButtonToExit::~ButtonToExit()
{

}

void ButtonToExit::Render(GraphicsEngine* _graphicsEngine)
{
	std::string renderText = text;
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(fontSize);
	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
	_graphicsEngine->ChangeFontSize(12.f);

	_graphicsEngine->DrawSprite("closebutton", 80, 1816, 42, 60, 60);
}

void ButtonToExit::OnButtonClicked()
{
	SoundManager::GetInstance()->Play(SoundManager::MOUSEEFFECT, SoundManager::BUTTON);
	GetManagers()->GetSceneManager()->GetCurrentScene()->DeleteAllObjects();
	SendMessage(gHWnd, WM_DESTROY, NULL, NULL);
}
