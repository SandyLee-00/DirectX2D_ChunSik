#include "Guardian.h"
#include "Monster.h"
#include "ShieldToDealer.h"
#include "RangeGuardianAttack.h"
#include "ManagerSet.h"
#include "RangeSupporterSheild.h"
#include "ShieldToGuardian.h"
#include "Supporter.h"
#include "ShieldFromGuardian.h"

Guardian::Guardian(ManagerSet* _managers)
	: Object("Guardian", _managers, OBJECT_TYPE::GUARDIAN, { 0, 0 }),
	postionInGrid{ 10, 7 },
	isGuardianShield(false)
	, isSupporterShield(false)
	, guardianShielElapsedTime(GURDIAN_SHIELD_MAXTIME)
	, supporterShieldElapsedTime(GURDIAN_SHIELD_MAXTIME)
	, shieldCoolTime(0.f)
	, animation(nullptr)
	, hitElapsedTime(0.0f)
	, supporter(nullptr)
	, shieldCoolTimeBarValue(0)
	, deadElapsedTime(0.0f)
{
	guardianState = GUARDIAN_STATE::IDLE;
	nextDirection = DIRECTION::NONE;
	lookDirection = DIRECTION::LEFT;
	HP = MAXHP;

	elapsedDistance = 0.0f;
	moveElapsedTime = 0.0f;

	moveSpeed = GRID_SIZE / MOVETIME;

	attackRange = nullptr;
	elapsedAttackReadyTime = 0.f;
	elapsedAttackTime = 0.f;

	guardianShield = nullptr;
	supporterShield = nullptr;
	targetMonster = nullptr;

	hpBar = nullptr;

	targetMonsterUID = -1;
}

Guardian::~Guardian()
{
	/*delete guardianShield;
	delete attackRange;
	delete supporterShield;
	delete targetMonster;
	delete hpBar;*/
}

void Guardian::Start()
{
	GetComponent<Transform>()->SetPosition(Grid::GetPostion(this->postionInGrid.x, this->postionInGrid.y));

	CreateComponent<BoxCollider>();
	this->GetManagers()->GetCollisionManager()->AddCollider(GetComponent<BoxCollider>());

	CreateComponent<Animation>();
	this->animation = GetComponent<Animation>();
	animation->SetOffset(Vector2{ -30,-70 });
	animation->SetSpriteRes(3, L"Animation\\Gdn\\GdnMove.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

	// FindTargetMonster();
}

void Guardian::Update(float _deltaTime)
{
	if (guardianState == GUARDIAN_STATE::IDLE)
	{
		UpdateIDLE(_deltaTime);
	}
	else if (guardianState == GUARDIAN_STATE::MOVE)
	{
		UpdateMOVE(_deltaTime);
	}
	else if (guardianState == GUARDIAN_STATE::ATTACK)
	{
		UpdateATTACK(_deltaTime);
	}
	else if (guardianState == GUARDIAN_STATE::HIT)
	{
		UpdateHIT(_deltaTime);
	}
	else if (guardianState == GUARDIAN_STATE::DEAD)
	{
		UpdateDEAD(_deltaTime);
	}

	// ����� ���ݹ��� ��Ÿ�ӽð� ������Ʈ
	elapsedAttackReadyTime += _deltaTime;

	// ������ �ǵ� �ɾ����� �ð� ���̴� �ڵ�
	supporterShieldElapsedTime -= _deltaTime;
	if (supporterShieldElapsedTime <= 0.f)
	{
		SetSupShield(false);
		this->supporterShieldElapsedTime = GURDIAN_SHIELD_MAXTIME;
	}

	// ����� �ǵ� ��Ÿ��
	// ���� ������ ����
	if (!isGuardianShield)
	{
		shieldCoolTime += _deltaTime;
		if (shieldCoolTime >= GURDIAN_SHIELD_COOLTIME + 1.f)
		{
			isGuardianShield = true;
			guardianShield->SetOnOff(true);
			shieldCoolTime = 0.f;
			this->supporterShield->SetOnOff(false);
			SoundManager::GetInstance()->Play(SoundManager::GUARDIANEFFECT, SoundManager::SHILDING);
		}
	}

	if (isGuardianShield == true)
	{
		guardianShielElapsedTime -= _deltaTime;
		if (guardianShielElapsedTime <= 0)
		{
			isGuardianShield = false;
			guardianShielElapsedTime = GURDIAN_SHIELD_MAXTIME;
		}
	}
}

void Guardian::FinalUpdate(float _deltaTime)
{

}

void Guardian::Render(GraphicsEngine* _graphicsEngine)
{
	// TODO: ����� ���ݿ� ���� �ִϸ��̼� ���ҽ� �޾Ƽ� �ֱ�
	// 
	if (guardianState == GUARDIAN_STATE::IDLE)
	{
		//���߿� Ȯ��
		//_graphicsEngine->DrawSprite("guar", 3, GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y, 154, 162);
	}
	else if (guardianState == GUARDIAN_STATE::MOVE)
	{
		if (this->lookDirection == DIRECTION::LEFT)
		{
			animation->SetSpriteRes(52, L"Animation\\Gdn\\GdnMoveL.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		if (this->lookDirection == DIRECTION::RIGHT)
		{

			animation->SetSpriteRes(53, L"Animation\\Gdn\\GdnMoveR.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
	}
	// ������� ������ ��
	else if (guardianState == GUARDIAN_STATE::ATTACK)
	{
		// ���� �� ��
		if (this->lookDirection == DIRECTION::LEFT)
		{
			animation->SetSpriteRes(77, L"Animation\\Gdn\\GdnAtkL.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y - 30);
		}
		// ������ �� ��
		else if (this->lookDirection == DIRECTION::RIGHT)
		{
			animation->SetSpriteRes(78, L"Animation\\Gdn\\GdnAtkR.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y - 30);
		}

	}

	// ������� �¾��� ��
	else if (guardianState == GUARDIAN_STATE::HIT)
	{
		// ���� �� ��
		if (this->lookDirection == DIRECTION::LEFT)
		{
			animation->SetSpriteRes(59, L"Animation\\Gdn\\GdnGetHitLeft.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		// ������ �� ��
		else if (this->lookDirection == DIRECTION::RIGHT)
		{
			animation->SetSpriteRes(60, L"Animation\\Gdn\\GdnGetHitRight.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}

	}
	// ������� �׾��� ��
	else if (guardianState == GUARDIAN_STATE::DEAD)
	{
		// ���� �� ��
		if (this->lookDirection == DIRECTION::LEFT)
		{
			if (!isDead)
			{
				animation->SetSpriteRes(57, L"Animation\\Gdn\\GdnDeathLeft.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			if (isDead)
			{
				animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}
		// ������ �� ��
		else if (this->lookDirection == DIRECTION::RIGHT)
		{
			if (!isDead)
			{
				animation->SetSpriteRes(58, L"Animation\\Gdn\\GdnDeathRight.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			if (isDead)
			{
				animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}

	}

	// ����� ü�¹� 5ĭ �׸���
	//������� ��ų�ٸ� �׸��ǵ�, 6�ʿ� �ѹ��� �������� �׸������̴�. 
	float TIMEGAP = GURDIAN_SHIELD_COOLTIME / (float)GURDIAN_SHIELD_BAR_MAX;
	shieldCoolTimeBarValue = (int)(shieldCoolTime / TIMEGAP);
	//shieldCoolTimeBarValue = (int)(shieldCoolTime / 5);

	// �׷��ִ� �κ� BackGroundOver�� �׸��� ��ġ �̵��ߴ� 

	if (this->isSupporterShield)
	{
		this->supporterShield->Render(_graphicsEngine);
	}
}

void Guardian::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Guardian";

	// state�� ���� update �ϱ�
	if (guardianState == GUARDIAN_STATE::IDLE)
	{
		stateString += " IDLE";
	}
	else if (guardianState == GUARDIAN_STATE::MOVE)
	{
		stateString += " MOVE";
	}
	else if (guardianState == GUARDIAN_STATE::ATTACK)
	{
		stateString += " ATTACK";
	}
	else if (guardianState == GUARDIAN_STATE::HIT)
	{
		stateString += " HIT";
	}
	else if (guardianState == GUARDIAN_STATE::DEAD)
	{
		stateString += " DEAD";
	}

	stateString += "\nHP: " + std::to_string(HP);

	_graphicsEngine->DrawString((int)position.x, (int)position.y, stateString);

	if (this->isSupporterShield)
	{
		//_graphicsEngine->DrawRectangle((int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y, 20, 20);
	}
}

void Guardian::OnCollisionEnter(Object* _other)
{

}

void Guardian::OnCollisionStay(Object* _other)
{
	if (_other->GetName() == "RangeSupporterSheild")
	{
		RangeSupporterSheild* rSS = dynamic_cast<RangeSupporterSheild*>(_other);
		if (rSS->GetOnOff())
		{
			this->isSupporterShield = true;
			this->supporterShield->SetOnOff(true);
			// TODO: ����� �ǵ� �ð� �´��� Ȯ���ϱ�
			supporterShieldElapsedTime = this->GURDIAN_SHIELD_MAXTIME;
		}

	}
}


void Guardian::OnCollisionExit(Object* _other)
{

}

// �̵����� ���� �Ǵ��� üũ�ϱ� -> �̵����� ���ϱ� -> �̵��ϱ�

void Guardian::UpdateIDLE(float _deltaTime)
{
	// IDLE Animation

	// ���� �̵����� ���ϱ�
	// LEFT / RIGHT / UP / DOWN
	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();
	Vector2 targetPosition;

	// 	if (targetMonster != nullptr)
	// 	{
	// 		targetPosition = targetMonster->GetComponent<Transform>()->GetPosition();
	// 		// Monster DEAD ���¸� 
	// 		// -> IDLE ���·� ���� X
	// 		// -> Ÿ�� ã��
	// 		if (targetMonster->GetGameState() == MONSTER_STATE::DEAD)
	// 		{
	// 			OutputDebugString(L"work\n");
	// 			targetMonster = nullptr;
	// 			// FindTargetMonster();
	// 
	// 			return;
	// 		}
	// 	}
	// 	// Ÿ�� ������ ������ �i�ư��� 
	// 	else if (targetMonster == nullptr)
	// 	{
	// 		targetPosition = supporter->GetComponent<Transform>()->GetPosition();
	// 		//targetPosition = Vector2(CENTER_POS_X, CENTER_POS_Y);
	// 	}

		/// @@@ ����� ������ ������ �����͸� ����ٴϰ� �ϱ� @@@
	targetPosition = supporter->GetComponent<Transform>()->GetPosition();
	Vector2 dir = targetPosition - position;

	int randValue = random::GetRandom<int>(0, 1);
	if (dir.x < 0 && dir.y > 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::LEFT;
		}
		else if (randValue == 1)
		{
			nextDirection = DIRECTION::DOWN;
		}
		else
		{
			nextDirection = DIRECTION::NONE;
		}
	}

	if (dir.x > 0 && dir.y > 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::RIGHT;
		}
		else if (randValue == 1)
		{
			nextDirection = DIRECTION::DOWN;
		}
		else
		{
			nextDirection = DIRECTION::NONE;
		}
	}
	if (dir.x < 0 && dir.y < 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::LEFT;
		}
		else if (randValue == 1)
		{
			nextDirection = DIRECTION::UP;
		}
		else
		{
			nextDirection = DIRECTION::NONE;
		}
	}
	if (dir.x > 0 && dir.y < 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::RIGHT;
		}
		else if (randValue == 1)
		{
			nextDirection = DIRECTION::UP;
		}
		else
		{
			nextDirection = DIRECTION::NONE;
		}
	}

	// ���� �ð��� ������ -> MOVE ���·� ����
	moveElapsedTime += _deltaTime;
	if (moveElapsedTime >= STOPTIME)
	{
		if (nextDirection == DIRECTION::LEFT)
		{
			this->postionInGrid.x--;
			lookDirection = DIRECTION::LEFT;
		}
		else if (nextDirection == DIRECTION::RIGHT)
		{
			this->postionInGrid.x++;
			lookDirection = DIRECTION::RIGHT;
		}
		else if (nextDirection == DIRECTION::UP)
		{
			this->postionInGrid.y--;
		}
		else if (nextDirection == DIRECTION::DOWN)
		{
			this->postionInGrid.y++;
		}
		else
		{
			return;
		}
		moveElapsedTime = 0.0f;
		guardianState = GUARDIAN_STATE::MOVE;

	}
}

void Guardian::UpdateMOVE(float _deltaTime)
{
	// Ÿ��, �� ��ġ ������Ʈ
	Transform* transform = GetComponent<Transform>();

	// ���� �̵����⿡ ���� �̵��ϱ�
	Vector2 moveVector = { 0, 0 };

	if (nextDirection == DIRECTION::LEFT)
	{
		// MoveLeft
		moveVector = { -1, 0 };
	}
	else if (nextDirection == DIRECTION::RIGHT)
	{
		// MoveRight
		moveVector = { 1, 0 };
	}
	else if (nextDirection == DIRECTION::UP)
	{
		// MoveUp
		moveVector = { 0, -1 };
	}
	else if (nextDirection == DIRECTION::DOWN)
	{
		// MoveDown
		moveVector = { 0, 1 };
	}
	transform->Translation(moveVector * _deltaTime * moveSpeed);

	// �̵��Ÿ��� �����Ÿ� �̻��̸� IDLE ���·� ����
	elapsedDistance += _deltaTime * moveSpeed;

	if (elapsedDistance >= GRID_SIZE)
	{
		elapsedDistance = 0.0f;
		guardianState = GUARDIAN_STATE::IDLE;
		transform->SetPosition(Grid::GetPostion(this->postionInGrid.x, this->postionInGrid.y));
	}
}

// ���� 1�ʵ��� ������ RangeGuardian Ȱ��ȭ
void Guardian::UpdateATTACK(float _deltaTime)
{
	// ATTACKTIME ������
	// -> ����� ���� IDLE�� �ٲٱ�
	// -> ����� ���� ���� OFF
	// -> ���� ���� ��Ÿ�� �ʱ�ȭ
	elapsedAttackTime += _deltaTime;
	if (elapsedAttackTime >= ATTACKTIME)
	{
		elapsedAttackTime = 0.0f;
		guardianState = GUARDIAN_STATE::IDLE;
		//attackRange->SetOnOff(false);
		elapsedAttackReadyTime = 0.0f;
		return;
	}

	// @@@@TargetMonster null üũ �� �ϱ� @@@@
	// Ÿ���� ������
	// -> IDLE ���·� ���� X
	// -> Ÿ�� ã��
	if (targetMonster == nullptr)
	{
		// FindTargetMonster();
		return;
	}

	// Monster DEAD ���¸� 
	// -> IDLE ���·� ���� X
	// -> Ÿ�� ã��
	if (targetMonster->GetGameState() == MONSTER_STATE::DEAD)
	{
		targetMonster = nullptr;
		// FindTargetMonster();

		return;
	}
}

void Guardian::UpdateHIT(float _deltaTime)
{
	hitElapsedTime += _deltaTime;
	if (hitElapsedTime >= HIT_EFFECTTIME)
	{
		hitElapsedTime = 0.0f;
		guardianState = GUARDIAN_STATE::IDLE;
		return;
	}
}

void Guardian::UpdateDEAD(float _deltaTime)
{
	deadElapsedTime += _deltaTime;
	if (deadElapsedTime >= DEAD_EFFECTTIME)
	{
		isDead = true;
		deadElapsedTime = 0.0f;
		//guardianState = GUARDIAN_STATE::IDLE;
		return;
	}
}

void Guardian::FindTargetMonster()
{
	// ���� ���� Add �� OBJECT_TYPE::MONSTER �������
	Scene* currentScene = this->GetManagers()->GetSceneManager()->GetCurrentScene();
	std::list<Object*>& objList = currentScene->GetObjectListType((int)(OBJECT_TYPE::MONSTER));

	for (auto obj : objList)
	{
		Monster* monster = dynamic_cast<Monster*>(obj);
		assert(monster != nullptr && "Wrong type. expended Monster but something different");
		Vector2 monsterPos = monster->GetComponent<Transform>()->GetPosition();

		bool isInside = false;

		// ���Ͱ� ȭ�� �ȿ� ������ true
		if (monsterPos.x > LIMIT_X_MIN && monsterPos.x < LIMIT_X_MAX &&
			monsterPos.y > LIMIT_Y_MIN && monsterPos.y < LIMIT_Y_MAX)
		{
			isInside = true;
		}

		// ���� IDLE / MOVE / HOLD ������ ��  && ȭ�� �ȿ� ������
		// -> ������� Ÿ������ ����
		if ((monster->GetGameState() == MONSTER_STATE::IDLE ||
			monster->GetGameState() == MONSTER_STATE::MOVE ||
			monster->GetGameState() == MONSTER_STATE::HOLD)
			&& isInside == true)
		{
			targetMonster = monster;
			std::wstring str = L"";
			Vector2 pos = targetMonster->GetComponent<Transform>()->GetPosition();
			str += std::to_wstring(pos.x);
			str += L", ";
			str += std::to_wstring(pos.y);
			OutputDebugString(str.c_str());
			targetMonsterUID = targetMonster->GetUID();
			break;
		}
	}
}

// �������� �� ������ �������� üũ
bool Guardian::CheckMoveable(float _x, float _y)
{
	// ȭ�� ������ ������ X
	if (_x < LIMIT_X_MIN || _x > LIMIT_X_MAX ||
		_y < LIMIT_Y_MIN || _y > LIMIT_Y_MAX)
	{
		return false;
	}

	// ���� ������ ���� X
	if (_x > LIMIT_X_DEALER_MIN && _x < LIMIT_X_DEALER_MAX &&
		_y > LIMIT_Y_DEALER_MIN && _y < LIMIT_Y_DEALER_MAX)
	{
		return false;
	}

	return true;
}

