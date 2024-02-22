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
	// 여기에 버튼 이미지 넣기
	_graphicsEngine->DrawSprite("skipbtn", 98, 1500, 100, 120, 40);
	// rm->LoadImage("skipbtn", pm->GetResourcePath(L"ui\\cutscene\\Opening_btn.png"));//98

	// 글자색 / 글자 크기 / 글자 위치 설정
	// Button에서 protected로 text / position / size를 받아옴
// 	std::string renderText = text;
// 	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
// 	_graphicsEngine->ChangeFontSize(fontSize);
// 	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
// 	_graphicsEngine->ChangeFontSize(12.f);
}
