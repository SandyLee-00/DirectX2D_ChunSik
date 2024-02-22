#include "CreditScene.h"

#include "BackGroundObject.h"
#include "ButtonToTitle.h"

CreditScene::CreditScene(ManagerSet* _managers)
	: Scene(_managers)
{

}

CreditScene::~CreditScene()
{

}

void CreditScene::Enter()
{
	// 위치 조정 편하게 하기
	const Vector2 POS_ButtonToTitle = { 1680, 960 };

	// 디버깅용 빈 오브젝트
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("CreditScene");
	managers->GetSceneManager()->AddObject(obj);

	// 타이틀로 돌아가는 버튼
	ButtonToTitle* buttonToTitle = new ButtonToTitle(this->managers);
	buttonToTitle->GetComponent<Transform>()->Translation(POS_ButtonToTitle);
	buttonToTitle->SetName("ButtonToTitle");
	buttonToTitle->SetSize(Vector2(215, 77));
	//buttonToTitle->SetTextAll("타이틀로 이동", POS_ButtonToTitle, 20.f);
	managers->GetSceneManager()->AddObject(buttonToTitle);

	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Title, true);
}

void CreditScene::Exit()
{
	//DeleteAllObjects();
	SoundManager::GetInstance()->Stop(SoundManager::BGM);
}
