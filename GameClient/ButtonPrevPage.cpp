#include "ButtonPrevPage.h"
#include "BackGroundObject.h"

ButtonPrevPage::ButtonPrevPage(ManagerSet* _managers)
	: Button(_managers)
{

}

ButtonPrevPage::~ButtonPrevPage()
{

}

void ButtonPrevPage::OnButtonClicked()
{
	SoundManager::GetInstance()->Play(SoundManager::MOUSEEFFECT, SoundManager::BUTTON);
	Scene* currentScene = GetManagers()->GetSceneManager()->GetCurrentScene();
	std::list<Object*>& objList = currentScene->GetObjectListType((int)(OBJECT_TYPE::BACK_GROUND));
	for (auto obj : objList)
	{
		// 배경 오브젝트 찾아서 -- 하기
		BackGroundObject* backGroundObject = dynamic_cast<BackGroundObject*>(obj);
		assert(backGroundObject != nullptr && "Wrong type. expended BackGroundObject but something different");

		backGroundObject->SetCurrentPage(backGroundObject->GetCurrentPage() - 1);
	}
}

void ButtonPrevPage::Render(GraphicsEngine* _graphicsEngine)
{
	// 여기에 버튼 이미지 넣기

	
}

void ButtonPrevPage::DebugRender(GraphicsEngine* _graphicsEngine)
{
	// 글자색 / 글자 크기 / 글자 위치 설정
	// Button에서 protected로 text / position / size를 받아옴
// 	std::string renderText = text;
// 	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
// 	_graphicsEngine->ChangeFontSize(fontSize);
// 	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
// 	_graphicsEngine->ChangeFontSize(12.f);
}
