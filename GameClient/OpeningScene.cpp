#include "OpeningScene.h"
#include "BackGroundObject.h"
#include "ManagerSet.h"
#include "ButtonOpeningSkip.h"
#include "ButtonNextPage.h"
#include "ButtonPrevPage.h"
#include "SoundManager.h"

OpeningScene::OpeningScene(ManagerSet* _managers)
	: Scene(_managers)
{

}

OpeningScene::~OpeningScene()
{

}

void OpeningScene::Enter()
{
	DeleteAllObjects();
	// 위치 조정 편하게 하기
	const Vector2 POS_ButtonOpeningSkip = { 1500, 100 };
	const Vector2 POS_ButtonNextPage = { 1500, 900 };
	const Vector2 POS_ButtonPrevPage = { 1350, 900 };

	// 버튼 크기조절 편하게 하기
	const Vector2 SIZE_Button = { 120, 40 };

	// 오프닝 페이지 최대 개수
	// 오프닝 컷신 3개
	const int OPENING_PAGE_MAX_COUNT = 3;

	// 디버깅용 빈 오브젝트
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("OpeningScene");
	obj->SetCurrentPage(0);
	obj->SetMaxPage(OPENING_PAGE_MAX_COUNT);
	managers->GetSceneManager()->AddObject(obj);

	// 스킵 버튼
	ButtonOpeningSkip* skip = new ButtonOpeningSkip(this->managers);
	skip->GetComponent<Transform>()->Translation(POS_ButtonOpeningSkip);
	skip->SetName("skip");
	skip->SetSize(SIZE_Button);
	skip->SetTextAll("", POS_ButtonOpeningSkip, 20.f);
	managers->GetSceneManager()->AddObject(skip);

	// 다음 페이지 버튼
	ButtonNextPage* buttonNextPage = new ButtonNextPage(this->managers);
	buttonNextPage->GetComponent<Transform>()->Translation(POS_ButtonNextPage);
	buttonNextPage->SetName("buttonNextPage");
	buttonNextPage->SetSize(SIZE_Button);
	buttonNextPage->SetTextAll("", POS_ButtonNextPage, 20.f);
	managers->GetSceneManager()->AddObject(buttonNextPage);

	// 이전 페이지 버튼
	ButtonPrevPage* buttonPrevPage = new ButtonPrevPage(this->managers);
	buttonPrevPage->GetComponent<Transform>()->Translation(POS_ButtonPrevPage);
	buttonPrevPage->SetName("buttonPrevPage");
	buttonPrevPage->SetSize(SIZE_Button);
	buttonPrevPage->SetTextAll("", POS_ButtonPrevPage, 20.f);
	managers->GetSceneManager()->AddObject(buttonPrevPage);

	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Opening, true);
}

void OpeningScene::Exit() 
{
	//DeleteAllObjects();
	//SoundManager::GetInstance()->MusicStop();
}
