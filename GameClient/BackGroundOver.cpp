#include "BackGroundOver.h"
#include "Guardian.h"
#include "Supporter.h"
#include "Dealer.h"

BackGroundOver::BackGroundOver(ManagerSet* _managers)
	: Object("BackGroundOver", _managers, OBJECT_TYPE::UI, (0.f, 0.f))
	, guardian(nullptr)
	, supporter(nullptr)
	, dealer(nullptr)
	, shieldGuardianCoolTimeBarValue(0)
	, shieldSupporterCoolTimeBarValue(0)
{

}

BackGroundOver::~BackGroundOver()
{

}

void BackGroundOver::Start()
{

}

void BackGroundOver::Update(float _deltaTime)
{
	Scene* scene = GetManagers()->GetSceneManager()->GetCurrentScene();
	
	// ����� ������ ��������
	if (guardian == nullptr)
	{
		std::list<Object*>& objList = scene->GetObjectListType((int)(OBJECT_TYPE::GUARDIAN));

		for (auto obj : objList)
		{
			guardian = dynamic_cast<Guardian*>(obj);
			assert(guardian != nullptr && "Wrong type. expended Guardian but something different");
		}
	}
	// ����� ��ų �� �� ��������
	if (guardian != nullptr)
	{
		shieldGuardianCoolTimeBarValue = guardian->GetShieldCoolTimeBarValue();
	}

	// ������ ������ ��������
	if (supporter == nullptr)
	{
		std::list<Object*>& objList = scene->GetObjectListType((int)(OBJECT_TYPE::SUPPORTER));

		for (auto obj : objList)
		{
			supporter = dynamic_cast<Supporter*>(obj);
			assert(supporter != nullptr && "Wrong type. expended Supporter but something different");
		}
	}

	// ������ ��ų �� �� �������
	if (supporter != nullptr)
	{
		//supporter->GetSkillCoolTimeBarValue();
		shieldSupporterCoolTimeBarValue = supporter->GetShieldCoolTimeBarValue();
	}

	// ���� ������ ��������

	// ���� ��ų �� �� �������
}

void BackGroundOver::FinalUpdate(float _deltaTime)
{

}

void BackGroundOver::Render(GraphicsEngine* _graphicsEngine)
{
	//_graphicsEngine->SetEffect(0.6f, 56);

	// �ڿ� �ִ� ����
	_graphicsEngine->DrawSprite("bgtree", 6, 0, 0, 1920, 1080);

	// ü�� �� �ؿ� �׸� �׸���
	_graphicsEngine->DrawSprite("interfaceOverHP", 81, 576, 984, 768, 96);

	// �� 3��
	_graphicsEngine->DrawSprite("dealFace", 69, 875, 973 + 34, 58, 58);
	_graphicsEngine->DrawSprite("gdnFace", 70, 1113, 973 + 34, 58, 58);
	_graphicsEngine->DrawSprite("supFace", 71, 637, 973 + 34, 58, 58);

	// ����� �� ���� ����ͼ� ���⼭ �׸���
	if (shieldGuardianCoolTimeBarValue == 5)
	{
		_graphicsEngine->DrawSprite("gskillbar1", 43, 1177, 1010 + 34, 102, 18);
	}
	else if (shieldGuardianCoolTimeBarValue == 4)
	{
		_graphicsEngine->DrawSprite("gskillbar2", 44, 1177, 1010 + 34, 102, 18);
	}
	else if (shieldGuardianCoolTimeBarValue == 3)
	{
		_graphicsEngine->DrawSprite("gskillbar3", 45, 1177, 1010 + 34, 102, 18);
	}
	else if (shieldGuardianCoolTimeBarValue == 2)
	{
		_graphicsEngine->DrawSprite("gskillbar4", 46, 1177, 1010 + 34, 102, 18);
	}
	else if (shieldGuardianCoolTimeBarValue == 1)
	{
		_graphicsEngine->DrawSprite("gskillbar5", 47, 1177, 1010 + 34, 102, 18);
	}
	else if (shieldGuardianCoolTimeBarValue <= 0)
	{
		_graphicsEngine->DrawSprite("gskillbar6", 48, 1177, 1010 + 34, 102, 18);
	}

	// ������ �� �� ����ͼ� ���⼭ �׸���
	if (shieldSupporterCoolTimeBarValue <= 0)
	{
		_graphicsEngine->DrawSprite("pskillbar1", 43, 701, 1010 + 34, 102, 18);
	}
	else if (shieldSupporterCoolTimeBarValue == 5)
	{
		_graphicsEngine->DrawSprite("pskillbar2", 44, 701, 1010 + 34, 102, 18);
	}
	else if (shieldSupporterCoolTimeBarValue == 4)
	{
		_graphicsEngine->DrawSprite("pskillbar3", 45, 701, 1010 + 34, 102, 18);
	}
	else if (shieldSupporterCoolTimeBarValue == 3)
	{
		_graphicsEngine->DrawSprite("pskillbar4", 46, 701, 1010 + 34, 102, 18);
	}
	else if (shieldSupporterCoolTimeBarValue == 2)
	{
		_graphicsEngine->DrawSprite("pskillbar5", 47, 701, 1010 + 34, 102, 18);
	}
	else if (shieldSupporterCoolTimeBarValue == 1)
	{
		_graphicsEngine->DrawSprite("pskillbar6", 48, 701, 1010 + 34, 102, 18);
	}

}

void BackGroundOver::DebugRender(GraphicsEngine* _graphicsEngine)
{

}
