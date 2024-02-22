#include "ButtonOpeningSkip.h"
#include "ClientHeaders.h"

ButtonOpeningSkip::ButtonOpeningSkip(ManagerSet* _managers)
	:Button(_managers)
{

}

ButtonOpeningSkip::~ButtonOpeningSkip()
{

}

void ButtonOpeningSkip::OnButtonClicked()
{
	SoundManager::GetInstance()->Play(SoundManager::MOUSEEFFECT, SoundManager::BUTTON);
	SceneManager* sceneManager = GetManagers()->GetSceneManager();
	sceneManager->ChangeScene("TutorialScene");
}

void ButtonOpeningSkip::Render(GraphicsEngine* _graphicsEngine)
{
	// ���⿡ ��ư �̹��� �ֱ�
	_graphicsEngine->DrawSprite("skipbtn", 98, 1500, 100, 120, 40);
	// rm->LoadImage("skipbtn", pm->GetResourcePath(L"ui\\cutscene\\Opening_btn.png"));//98
}

void ButtonOpeningSkip::DebugRender(GraphicsEngine* _graphicsEngine)
{
	// ���ڻ� / ���� ũ�� / ���� ��ġ ����
	// Button���� protected�� text / position / size�� �޾ƿ�
	std::string renderText = text;
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(fontSize);
	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
	_graphicsEngine->ChangeFontSize(12.f);
}
