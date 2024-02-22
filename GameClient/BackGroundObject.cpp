#include "BackGroundObject.h"

BackGroundObject::BackGroundObject(ManagerSet* _managers)
	: Object("BackGroundObject", _managers, OBJECT_TYPE::BACK_GROUND, (0.f, 0.f))
{
	currentPage = 0;
	maxPage = 0;
}

BackGroundObject::~BackGroundObject()
{

}

void BackGroundObject::Start()
{

}

void BackGroundObject::Update(float _deltaTime)
{
	KeyManager* keyManager = this->GetManagers()->GetKeyManager();

	if(keyManager->GetKeyState(KEY::LEFT) == KEY_STATE::DOWN)
	{
		currentPage--;
	}
	else if (keyManager->GetKeyState(KEY::RIGHT) == KEY_STATE::DOWN)
	{
		currentPage++;
	}

	// 0�������ε� ���� ������ ������ 0������ ����
	if (currentPage < 0)
	{
		currentPage = 0;
	}

	// �ִ� �������ε� ���� ������ ������ TutorialScene ������ �Ѿ��
	if (currentPage >= maxPage && this->GetName() == "OpeningScene")
	{
		this->GetManagers()->GetSceneManager()->ChangeScene("TutorialScene");
		currentPage = 0;
	}
	// �ִ� �������ε� ���� ������ ������ MainGameScene ������ �Ѿ��
	else if (currentPage >= maxPage && this->GetName() == "TutorialScene")
	{
		this->GetManagers()->GetSceneManager()->ChangeScene("MainGameScene");
		currentPage = 0;
	}
}

void BackGroundObject::FinalUpdate(float _deltaTime)
{

}

// ��ü ȭ�� ��� �׸��� ���� ���⿡ �ֱ�
void BackGroundObject::Render(GraphicsEngine* _graphicsEngine)
{

	if (this->GetName() == "TitleScene")
	{
		// Ÿ��Ʋ ȭ�� ��� �׸���
		_graphicsEngine->DrawSprite("title", 94, 0, 0, 1920, 1080);
	}
	// ������ �ƽ� 3��
	else if (this->GetName() == "OpeningScene")
	{
		if (currentPage <= 0)
		{
			// OpeningScene ù��° ��� �׸���
			_graphicsEngine->DrawSprite("opening1", 73, 0, 0, 1920, 1080);
		}

		else if (currentPage == 1)
		{
			// OpeningScene �ι�° ��� �׸���
			_graphicsEngine->DrawSprite("opening2", 74, 0, 0, 1920, 1080);
		}

		else if (currentPage >= 2)
		{
			// OpeningScene ����° ��� �׸���
			_graphicsEngine->DrawSprite("opening3", 75, 0, 0, 1920, 1080);
		}
	}

	// Ʃ�丮�� ������ 7��
	else if (this->GetName() == "TutorialScene")
	{
		if (currentPage <= 0)
		{
			// TutorialScene ù��° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial1", 87, 0, 0, 1920, 1080);
		}
		else if (currentPage == 1)
		{
			// TutorialScene �ι�° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial2", 88, 0, 0, 1920, 1080);
		}
		else if (currentPage == 2)
		{
			// TutorialScene ����° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial3", 89, 0, 0, 1920, 1080);
		}
		else if (currentPage == 3)
		{
			// TutorialScene �׹�° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial4", 90, 0, 0, 1920, 1080);
		}
		else if (currentPage == 4)
		{
			// TutorialScene �ټ���° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial5", 91, 0, 0, 1920, 1080);
		}
		else if (currentPage == 5)
		{
			// TutorialScene ������° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial6", 92, 0, 0, 1920, 1080);
		}
		else if (currentPage >= 6)
		{
			// TutorialScene �ϰ���° ��� �׸���
			_graphicsEngine->DrawSprite("tutorial7", 93, 0, 0, 1920, 1080);
		}

	}
	else if (this->GetName() == "MainGameScene")
	{
		_graphicsEngine->DrawSprite("bg", 5, 0, 0, 1920, 1080);

		_graphicsEngine->DrawSprite("bgtree", 6, 0, 0, 1920, 1080);


	}
	else if (this->GetName() == "RankingScene")
	{
		_graphicsEngine->DrawSprite("dummy", 25, 0, 0, 1920, 1080);
	}
	else if (this->GetName() == "CreditScene")
	{
		// ũ���� �� ��� �׸���
		_graphicsEngine->DrawSprite("credit", 100, 0, 0, 1920, 1080);
	}


}

void BackGroundObject::DebugRender(GraphicsEngine* _graphicsEngine)
{

	TimeManager* tm = this->GetManagers()->GetTimeManager();

	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	// ���� ũ�� Ű���
	_graphicsEngine->ChangeFontSize(30.f);

	std::string printString = "";
	printString += "currentPage : " + std::to_string(currentPage) + "\n";
	printString += "maxPage : " + std::to_string(maxPage) + "\n";

	// ������ ������
	printString += "FPS : " + std::to_string((int)(1.f / tm->GetfDT())) + "\n";

	// ���������� �� ������Ʈ ���� ������ֱ�
	_graphicsEngine->DrawString(0, 0, printString + "_DEBUG");

	// ���� ũ�� �ǵ�����
	_graphicsEngine->ChangeFontSize(12.f);

}
