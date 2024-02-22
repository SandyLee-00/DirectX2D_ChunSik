#include "ShieldFromSupporter.h"
#include "Guardian.h"
#include "Dealer.h"

ShieldFromSupporter::ShieldFromSupporter(ManagerSet* _managers)
	: Object("ShieldFromSupporter", _managers, OBJECT_TYPE::EEFECT, { 0, 0 })
	, dealShieldAnimation(nullptr)
	, dealer(nullptr)
	, guardian(nullptr)
	, dealerTransform(nullptr)
	, guardTransform(nullptr)
	, guardShieldAnimation(nullptr)
{
	parent = nullptr;
	target = nullptr;
	isOnOff = false;
}

ShieldFromSupporter::~ShieldFromSupporter()
{

}

void ShieldFromSupporter::Start()
{
	/*auto col = this->CreateComponent<BoxCollider>();
	col->SetSize(288, 288);
	this->GetManagers()->GetCollisionManager()->AddCollider(col);*/



	dealShieldAnimation = CreateComponent<Animation>();
	//dealShieldAnimation = GetComponent<Animation>();
	dealShieldAnimation->SetOffset(Vector2{ -10,-30 });
	dealShieldAnimation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
	guardShieldAnimation = CreateComponent<Animation>();
	//guardShieldAnimation = GetComponent<Animation>();
	guardShieldAnimation->SetOffset(Vector2{ -10,-30 });
	guardShieldAnimation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

void ShieldFromSupporter::Update(float _deltaTime)
{
	// maingamescene���� ������

	dealerTransform = CreateComponent<Transform>();
	dealerTransform = dealer->GetComponent<Transform>();

	guardTransform = guardian->GetComponent<Transform>();


	Vector2 offset = { 0,0 };
	Vector2 dealerShieldPos = dealerTransform->GetPosition();
	dealerTransform->SetPosition(dealerShieldPos + offset);
	Vector2 guardianShieldPos = guardTransform->GetPosition();
	guardTransform->SetPosition(guardianShieldPos + offset);

}

void ShieldFromSupporter::FinalUpdate(float _deltaTime)
{

}

void ShieldFromSupporter::Render(GraphicsEngine* _graphicsEngine)
{
	if (isOnOff == true)
	{
		if (dealer->GetSupShield())
		{
			dealShieldAnimation->SetSpriteRes(49, L"Animation\\ShieldEft.txt", "shieldeft", (int)dealerTransform->GetPosition().x - 5, (int)dealerTransform->GetPosition().y - 30);
		}
		if (guardian->GetSupShield())
		{
			guardShieldAnimation->SetSpriteRes(49, L"Animation\\ShieldEft.txt", "shieldeft", (int)guardTransform->GetPosition().x + 20, (int)guardTransform->GetPosition().y + 30);
		}
		if (dealer->GetSupShield() && guardian->GetSupShield())
		{
			dealShieldAnimation->SetSpriteRes(49, L"Animation\\ShieldEft.txt", "shieldeft", (int)dealerTransform->GetPosition().x - 5, (int)dealerTransform->GetPosition().y - 30);
			guardShieldAnimation->SetSpriteRes(49, L"Animation\\ShieldEft.txt", "shieldeft", (int)guardTransform->GetPosition().x + 20, (int)guardTransform->GetPosition().y + 30);
		}
	}


	// ���� �ִϸ��̼� ��� �ϴ°�
	// ������ ��������Ʈ�� �ִϸ��̼� �����
	if (isOnOff == false)
	{
		//animation->Stop();
		dealShieldAnimation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x + 20, (int)GetComponent<Transform>()->GetPosition().y + 30);
	}
}

void ShieldFromSupporter::DebugRender(GraphicsEngine* _graphicsEngine)
{
	//// ������Ʈ �ǵ�, ���� �ʿ� ���� 0,0���� ������ �׷�����.
	//Vector2 position = this->GetComponent<Transform>()->GetPosition();
	//std::string stateString = "RangeSupporterSheild";
	//if (isOnOff)
	//{
	//	Vector2 tmp = SHEILD_RANGE + position;
	//	_graphicsEngine->DrawRectangle(position.x, position.y, tmp.x, tmp.y);
	//}
	//else
	//{

	//}
}

// TODO shield�� ���� ��ü�� �ߴµ� collision�� ��� �����ϴ��� ��
void ShieldFromSupporter::OnCollisionEnter(Object* _other)
{

}

void ShieldFromSupporter::OnCollisionStay(Object* _other)
{

}

void ShieldFromSupporter::OnCollisionExit(Object* _other)
{

}
