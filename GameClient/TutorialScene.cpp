#include "TutorialScene.h"
#include "ClientHeaders.h"
#include "BackGroundObject.h"
#include "ButtonTutorialSkip.h"
#include "ButtonNextPage.h"
#include "ButtonPrevPage.h"

TutorialScene::TutorialScene(ManagerSet* _managers)
	: Scene(_managers)
{
}

TutorialScene::~TutorialScene()
{

}

void TutorialScene::Enter()
{
	
	DeleteAllObjects();
	// ��ġ ���� ���ϰ� �ϱ�
	const Vector2 POS_ButtonTutorialSkip = { 1500, 100 };
	const Vector2 POS_ButtonNextPage = { 1500, 900 };
	const Vector2 POS_ButtonPrevPage = { 1350, 900 };

	// ��ư ũ������ ���ϰ� �ϱ�
	const Vector2 SIZE_Button = { 120, 40 };

	// Ʃ�丮�� ������ �ִ� ����
	// Ʃ�丮�� �ƽ� 7��
	const int TUTORIAL_PAGE_MAX_COUNT = 7;

	// ������ �� ������Ʈ
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("TutorialScene");
	obj->SetCurrentPage(0);
	obj->SetMaxPage(TUTORIAL_PAGE_MAX_COUNT);
	managers->GetSceneManager()->AddObject(obj);

	// Ʃ�丮�� ��ŵ
	ButtonTutorialSkip* buttonTutorialSkip = new ButtonTutorialSkip(this->managers);
	buttonTutorialSkip->GetComponent<Transform>()->Translation(POS_ButtonTutorialSkip);
	buttonTutorialSkip->SetName("buttonTutorialSkip");
	buttonTutorialSkip->SetSize(SIZE_Button);
	buttonTutorialSkip->SetTextAll("", POS_ButtonTutorialSkip, 20.f);
	managers->GetSceneManager()->AddObject(buttonTutorialSkip);

	// ���� ������ ��ư
	ButtonNextPage* buttonNextPage = new ButtonNextPage(this->managers);
	buttonNextPage->GetComponent<Transform>()->Translation(POS_ButtonNextPage);
	buttonNextPage->SetName("buttonNextPage");
	buttonNextPage->SetSize(SIZE_Button);
	buttonNextPage->SetTextAll("", POS_ButtonNextPage, 20.f);
	managers->GetSceneManager()->AddObject(buttonNextPage);

	// ���� ������ ��ư
	ButtonPrevPage* buttonPrevPage = new ButtonPrevPage(this->managers);
	buttonPrevPage->GetComponent<Transform>()->Translation(POS_ButtonPrevPage);
	buttonPrevPage->SetName("buttonPrevPage");
	buttonPrevPage->SetSize(SIZE_Button);
	buttonPrevPage->SetTextAll("", POS_ButtonPrevPage, 20.f);
	managers->GetSceneManager()->AddObject(buttonPrevPage);

}

void TutorialScene::Exit()
{
	//DeleteAllObjects();
	SoundManager::GetInstance()->Stop(SoundManager::BGM);
}
