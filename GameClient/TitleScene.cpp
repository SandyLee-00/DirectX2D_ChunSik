#include "TitleScene.h"
#include "ClientHeaders.h"

#include "BackGroundObject.h"

#include "ButtonToCredit.h"
#include "ButtonToGame.h"
#include "ButtonToOptions.h"
#include "ButtonToRanking.h"
#include "SoundManager.h"
#include "ButtonToExit.h"

TitleScene::TitleScene(ManagerSet* _manager)
	: Scene(_manager)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Enter()
{
	DeleteAllObjects();
	// 위치 조정 편하게 하기
	const Vector2 POS_ButtonToGame = { 747, 722 };
	const Vector2 POS_ButtonToRanking = { 747, 845 };
	const Vector2 POS_ButtonToCredit = { 971, 845 };
	const Vector2 POS_ButtonToExit = { 1816,42 };

	// 사이즈 조정 편하게 하기
	const Vector2 SIZE_ButtonToGame = { 426, 104 };
	const Vector2 SIZE_ButtonToRanking = { 202, 70 };
	const Vector2 SIZE_ButtonToCredit = { 202, 70 };
	const Vector2 SIZE_ButtonToExit = { 60, 60 };

	// 디버깅용 빈 오브젝트
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("TitleScene");
	managers->GetSceneManager()->AddObject(obj);

	// 시작
	ButtonToGame* buttonToGame = new ButtonToGame(this->managers);
	buttonToGame->GetComponent<Transform>()->Translation(POS_ButtonToGame);
	buttonToGame->SetName("ButtonToGame");
	buttonToGame->SetSize(SIZE_ButtonToGame);
	buttonToGame->SetTextAll("", POS_ButtonToGame, 30.f);
	managers->GetSceneManager()->AddObject(buttonToGame);

	ButtonToRanking* buttonToRanking = new ButtonToRanking(this->managers);
	buttonToRanking->GetComponent<Transform>()->Translation(POS_ButtonToRanking);
	buttonToRanking->SetName("ButtonToRanking");
	buttonToRanking->SetSize(SIZE_ButtonToRanking);
	buttonToRanking->SetTextAll("", POS_ButtonToRanking, 20.f);
	managers->GetSceneManager()->AddObject(buttonToRanking);

	ButtonToCredit* buttonToCredit = new ButtonToCredit(this->managers);
	buttonToCredit->GetComponent<Transform>()->Translation(POS_ButtonToCredit);
	buttonToCredit->SetName("ButtonToCredit");
	buttonToCredit->SetSize(SIZE_ButtonToCredit);
	buttonToCredit->SetTextAll("", POS_ButtonToCredit, 20.f);
	managers->GetSceneManager()->AddObject(buttonToCredit);

	ButtonToExit* buttonToExit = new ButtonToExit(this->managers);
	buttonToExit->GetComponent<Transform>()->Translation(POS_ButtonToExit);
	buttonToExit->SetName("ButtonToExit");
	buttonToExit->SetSize(SIZE_ButtonToExit);
	buttonToExit->SetTextAll("종료", POS_ButtonToExit, 20.f);
	managers->GetSceneManager()->AddObject(buttonToExit);


	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Title, true);
}

void TitleScene::Exit()
{
	//DeleteAllObjects();
	SoundManager::GetInstance()->Stop(SoundManager::BGM);
}
