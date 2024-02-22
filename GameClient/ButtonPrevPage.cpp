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
		// ��� ������Ʈ ã�Ƽ� -- �ϱ�
		BackGroundObject* backGroundObject = dynamic_cast<BackGroundObject*>(obj);
		assert(backGroundObject != nullptr && "Wrong type. expended BackGroundObject but something different");

		backGroundObject->SetCurrentPage(backGroundObject->GetCurrentPage() - 1);
	}
}

void ButtonPrevPage::Render(GraphicsEngine* _graphicsEngine)
{
	// ���⿡ ��ư �̹��� �ֱ�

	
}

void ButtonPrevPage::DebugRender(GraphicsEngine* _graphicsEngine)
{
	// ���ڻ� / ���� ũ�� / ���� ��ġ ����
	// Button���� protected�� text / position / size�� �޾ƿ�
// 	std::string renderText = text;
// 	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
// 	_graphicsEngine->ChangeFontSize(fontSize);
// 	_graphicsEngine->DrawString((int)stringPosition.x, (int)stringPosition.y, renderText);
// 	_graphicsEngine->ChangeFontSize(12.f);
}
