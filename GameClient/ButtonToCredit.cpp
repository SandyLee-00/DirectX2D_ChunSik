#include "ButtonToCredit.h"

ButtonToCredit::ButtonToCredit(ManagerSet* _managers)
	: Button(_managers)
{

}

ButtonToCredit::~ButtonToCredit()
{

}

void ButtonToCredit::Render(GraphicsEngine* _graphicsEngine)
{
	// ���⿡ ��ư �̹��� �ֱ�

	// ���ڻ� / ���� ũ�� / ���� ��ġ ����
	// Button���� protected�� text / position / size�� �޾ƿ�
// 	std::string renderText = text;
// 	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
// 	_graphicsEngine->ChangeFontSize(fontSize);
// 	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
// 	_graphicsEngine->ChangeFontSize(12.f);

	// ���⿡ ��ư �̹��� �ֱ�

	_graphicsEngine->DrawSprite("creditbtn", 95, 971, 845, 202, 70);

	// 	rm->LoadImage("creditbtn", pm->GetResourcePath(L"ui\\title_btn\\UI_Credit_btn.png"));//95
	// 	rm->LoadImage("rankingbtn", pm->GetResourcePath(L"ui\\title_btn\\UI_Rank_btn.png"));//96
	// 	rm->LoadImage("startbtn", pm->GetResourcePath(L"ui\\title_btn\\UI_Start_btn.png"));//97
}

void ButtonToCredit::OnButtonClicked()
{
	SoundManager::GetInstance()->Play(SoundManager::MOUSEEFFECT, SoundManager::BUTTON);
	SceneManager* sceneManager = GetManagers()->GetSceneManager();
	sceneManager->ChangeScene("CreditScene");
}

