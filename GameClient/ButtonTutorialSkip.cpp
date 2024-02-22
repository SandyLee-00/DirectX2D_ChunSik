#include "ButtonTutorialSkip.h"
#include "ClientHeaders.h"

ButtonTutorialSkip::ButtonTutorialSkip(ManagerSet* _managers)
	: Button(_managers)
{
}

ButtonTutorialSkip::~ButtonTutorialSkip()
{

}

void ButtonTutorialSkip::OnButtonClicked()
{
	SoundManager::GetInstance()->Play(SoundManager::MOUSEEFFECT, SoundManager::BUTTON);
	SceneManager* sceneManager = GetManagers()->GetSceneManager();
	sceneManager->ChangeScene("MainGameScene");
}

void ButtonTutorialSkip::Render(GraphicsEngine* _graphicsEngine)
{
	// ���⿡ ��ư �̹��� �ֱ�
	_graphicsEngine->DrawSprite("skipbtn", 98, 1500, 100, 120, 40);
	// rm->LoadImage("skipbtn", pm->GetResourcePath(L"ui\\cutscene\\Opening_btn.png"));//98

	// ���ڻ� / ���� ũ�� / ���� ��ġ ����
	// Button���� protected�� text / position / size�� �޾ƿ�
// 	std::string renderText = text;
// 	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
// 	_graphicsEngine->ChangeFontSize(fontSize);
// 	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
// 	_graphicsEngine->ChangeFontSize(12.f);
}
