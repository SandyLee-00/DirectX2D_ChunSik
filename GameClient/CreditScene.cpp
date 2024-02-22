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
	// ��ġ ���� ���ϰ� �ϱ�
	const Vector2 POS_ButtonToTitle = { 1680, 960 };

	// ������ �� ������Ʈ
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("CreditScene");
	managers->GetSceneManager()->AddObject(obj);

	// Ÿ��Ʋ�� ���ư��� ��ư
	ButtonToTitle* buttonToTitle = new ButtonToTitle(this->managers);
	buttonToTitle->GetComponent<Transform>()->Translation(POS_ButtonToTitle);
	buttonToTitle->SetName("ButtonToTitle");
	buttonToTitle->SetSize(Vector2(215, 77));
	//buttonToTitle->SetTextAll("Ÿ��Ʋ�� �̵�", POS_ButtonToTitle, 20.f);
	managers->GetSceneManager()->AddObject(buttonToTitle);

	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Title, true);
}

void CreditScene::Exit()
{
	//DeleteAllObjects();
	SoundManager::GetInstance()->Stop(SoundManager::BGM);
}
