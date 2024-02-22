#include "Monster.h"
#include "Dealer.h"
#include "Guardian.h"
#include "Supporter.h"
#include "FrozEffect.h"
#include "BarDealerZ.h"
#include "TextFrozenCount.h"
#include "GuardianAttackEffect.h"

Monster::Monster(ManagerSet* _managers)
	: Object("Monster", _managers, OBJECT_TYPE::MONSTER, { 0, 0 })
	, moveElapsedTime(0.0f)
	, elapsedDistance(0.0f)
	, monsterState(MONSTER_STATE::IDLE)
	, nextDirection(DIRECTION::NONE)
	, moveSpeed(GRID_SIZE / this->TWO_MOVETIME)
	, OWNSTOPTIME(this->TWO_STOPTIME)
	, postionInGrid{ 0,0 }
	, monsterType(MONSTER_TYPE::TWO)
	, monsterPool(nullptr)
	, UID(0)
	, deadElapsedTime(0.0f)
	, lookDirection(DIRECTION::LEFT)
	, deadReadyElapsedTime(0.0f)
	, frozEffect(nullptr)
	, isScoreOn(false)
	, elapsedTime(0.0f)
	, eachMonsterScore(0)
	, gdnAtkEft(nullptr)
	, getGdnHitTime(0.f)
	, getGdnHit(false)
	, pastFrozen(false)
	, DZ(nullptr)
	, TF(nullptr)
{
	this->SetCanPause(true);
}

Monster::~Monster()
{

}

// TODO: this->GetManagers()->GetCollisionManager()->AddCollider(collider); �̺κп��� ������
void Monster::Start()
{
	auto collider = CreateComponent<BoxCollider>();
	assert(collider && "cannot make collider at monster\n");
	collider->SetOffset({ 48 - 25, 48 - 25 });
	collider->SetSize({ 50, 50 });
	this->GetManagers()->GetCollisionManager()->AddCollider(collider);

	Transform* transform = GetComponent<Transform>();
	transform->SetPosition({ 200, 700 });

	animation = CreateComponent<Animation>();
	animation->SetOffset(Vector2{ 13,0 });

	animation->SetSpriteRes(27, L"Animation\\nullptr.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

}

void Monster::Update(float _deltaTime)
{
	// state�� ���� update �ϱ�
	if (monsterState == MONSTER_STATE::IDLE)
	{
		UpdateIDLE(_deltaTime);
	}
	else if (monsterState == MONSTER_STATE::MOVE)
	{
		UpdateMOVE(_deltaTime);
	}
	else if (monsterState == MONSTER_STATE::DEAD_READY)
	{
		UpdateDEAD_READY(_deltaTime);
	}
	else if (monsterState == MONSTER_STATE::DEAD)
	{
		UpdateDEAD(_deltaTime);
	}
	else if (monsterState == MONSTER_STATE::HOLD)
	{
		UpdateHOLD(_deltaTime);
	}
	else if (monsterState == MONSTER_STATE::HOLD_DEAD_READY)
	{
		UpdateHOLD_DEAD_READY(_deltaTime);
	}

	// ���� ����Ʈ isScoreOn �Ǹ� ������ �ð� ������ Off �ϱ�
	if (isScoreOn == true)
	{
		elapsedTime += _deltaTime;
		if (elapsedTime >= EACH_MONSTER_SCORE_EFFECTIME)
		{
			elapsedTime = 0.0f;
			isScoreOn = false;
			eachMonsterScore = 0;
		}
	}
}

void Monster::FinalUpdate(float _deltaTime)
{

}

void Monster::Render(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	Transform* transform = GetComponent<Transform>();

	// state�� ���� render �ϱ�
	// _graphicsEngine->DrawEmptyRect((int)position.x, (int)position.y, (int)position.x + 10, (int)position.y + 10);

	int drawsheet = 1;
	if (monsterType == MONSTER_TYPE::TWO)
	{
		drawsheet = 1;
		if (lookDirection == DIRECTION::LEFT)
		{
			if (monsterState == MONSTER_STATE::IDLE)
			{
				animation->SetSpriteRes(1, L"Animation\\Mon\\Mon1IdleL.txt", "mon1IdleL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::MOVE)
			{
				animation->SetSpriteRes(18, L"Animation\\Mon\\Mon1MoveLeft.txt", "mon1MoveL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			// DEAD_READY������ IDLE
			if (monsterState == MONSTER_STATE::DEAD_READY)
			{
				animation->SetSpriteRes(1, L"Animation\\Mon\\Mon1IdleL.txt", "mon1IdleL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::DEAD)
			{
				animation->SetSpriteRes(23, L"Animation\\Mon\\MonDeath.txt", "monDeath", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			else if (monsterState == MONSTER_STATE::HOLD)
			{
				animation->SetSpriteRes(32, L"Animation\\Mon\\Mon1HoldL.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::HOLD_DEAD_READY)
			{
				animation->SetSpriteRes(32, L"Animation\\Mon\\Mon1HoldL.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}
		if (lookDirection == DIRECTION::RIGHT)
		{
			if (monsterState == MONSTER_STATE::IDLE)
			{
				animation->SetSpriteRes(29, L"Animation\\Mon\\Mon1IdleR.txt", "mon1IdleR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::MOVE)
			{
				animation->SetSpriteRes(19, L"Animation\\Mon\\Mon1MoveRight.txt", "mon1MoveR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			// DEAD_READY������ IDLE
			else if (monsterState == MONSTER_STATE::DEAD_READY)
			{
				animation->SetSpriteRes(29, L"Animation\\Mon\\Mon1IdleR.txt", "mon1IdleR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::DEAD)
			{
				animation->SetSpriteRes(23, L"Animation\\Mon\\MonDeath.txt", "monDeath", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			else if (monsterState == MONSTER_STATE::HOLD)
			{
				animation->SetSpriteRes(33, L"Animation\\Mon\\Mon1HoldR.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::HOLD_DEAD_READY)
			{
				animation->SetSpriteRes(33, L"Animation\\Mon\\Mon1HoldR.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}

	}
	else if (monsterType == MONSTER_TYPE::THREE)
	{
		drawsheet = 2;
		if (lookDirection == DIRECTION::LEFT)
		{
			if (monsterState == MONSTER_STATE::IDLE)
			{
				animation->SetSpriteRes(2, L"Animation\\Mon\\Mon2IdleL.txt", "mon2IdleL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::MOVE)
			{
				animation->SetSpriteRes(20, L"Animation\\Mon\\Mon2MoveLeft.txt", "mon2MoveL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			// DEAD_READY������ IDLE
			else if (monsterState == MONSTER_STATE::DEAD_READY)
			{
				animation->SetSpriteRes(2, L"Animation\\Mon\\Mon2IdleL.txt", "mon2IdleL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::DEAD)
			{
				animation->SetSpriteRes(23, L"Animation\\Mon\\MonDeath.txt", "monDeath", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			else if (monsterState == MONSTER_STATE::HOLD)
			{
				animation->SetSpriteRes(31, L"Animation\\Mon\\Mon2HoldL.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::HOLD_DEAD_READY)
			{
				animation->SetSpriteRes(31, L"Animation\\Mon\\Mon2HoldL.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}
		if (lookDirection == DIRECTION::RIGHT)
		{
			if (monsterState == MONSTER_STATE::IDLE)
			{
				animation->SetSpriteRes(30, L"Animation\\Mon\\Mon2IdleR.txt", "mon2IdleR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::MOVE)
			{
				animation->SetSpriteRes(21, L"Animation\\Mon\\Mon2MoveRight.txt", "mon2MoveR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			// DEAD_READY������ IDLE
			else if (monsterState == MONSTER_STATE::DEAD_READY)
			{
				animation->SetSpriteRes(30, L"Animation\\Mon\\Mon2IdleR.txt", "mon2IdleR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::DEAD)
			{
				animation->SetSpriteRes(23, L"Animation\\Mon\\MonDeath.txt", "monDeath", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);

			}
			else if (monsterState == MONSTER_STATE::HOLD)
			{
				animation->SetSpriteRes(22, L"Animation\\Mon\\Mon2HoldR.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			else if (monsterState == MONSTER_STATE::HOLD_DEAD_READY)
			{
				animation->SetSpriteRes(22, L"Animation\\Mon\\Mon2HoldR.txt", "monHold", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}
	}

	// ���� ���� isScoreOn �Ǹ� �׸���
	// __________________________________
	const int OFFSET_X = 20;
	const int OFFSET_Y = -30;

	if (isScoreOn == true)
	{
		// �׸��� �� �� ����
		_graphicsEngine->ChangeFontSize(25.f);
		_graphicsEngine->ColorSet(D2D1::ColorF::White);

		// ���� �׸���
		std::string scoreString = "";
		scoreString += "+ ";
		scoreString += std::to_string(this->eachMonsterScore);

		_graphicsEngine->DrawString((int)position.x + OFFSET_X, (int)position.y + OFFSET_Y, scoreString);

		// �׸� �� �� �ǵ�����
		_graphicsEngine->ColorSet(D2D1::ColorF::Black);
		_graphicsEngine->ChangeFontSize(12.f);
	}
}

void Monster::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Monster";

	// state�� ���� update �ϱ�
	if (monsterState == MONSTER_STATE::IDLE)
	{
		stateString += " IDLE";
	}
	else if (monsterState == MONSTER_STATE::MOVE)
	{
		stateString += " MOVE";
	}
	else if (monsterState == MONSTER_STATE::DEAD)
	{
		stateString += " DEAD";
	}
	else if (monsterState == MONSTER_STATE::DEAD_READY)
	{
		stateString += " DEAD_READY";
	}
	else if (monsterState == MONSTER_STATE::HOLD)
	{
		stateString += " HOLD";
	}

	if (nextDirection == DIRECTION::LEFT)
	{
		stateString += " LEFT";
	}
	else if (nextDirection == DIRECTION::RIGHT)
	{
		stateString += " RIGHT";
	}
	else if (nextDirection == DIRECTION::UP)
	{
		stateString += " UP";
	}
	else if (nextDirection == DIRECTION::DOWN)
	{
		stateString += " DOWN";
	}

	stateString += " " + std::to_string(UID);
	_graphicsEngine->DrawString((int)position.x, (int)position.y, stateString);

}

void Monster::OnCollisionEnter(Object* _other)
{
	/*

	// ���Ͱ� MOVE �� �� �ε��� ������Ʈ�� ������ ���
	if (monsterState == MONSTER_STATE::MOVE &&
		_collision->collider1->GetOwner()->GetName() == "Dealer")
	{
		monsterState = MONSTER_STATE::DEAD;
	}

	*/

	// 1. ������ �浹���� ��
	// -> �� ���� DEAD�� ����
	// Dealer : ���� ���� HIT / HP--
	if (_other->GetName() == "Dealer")
	{
		if (this->monsterState == MONSTER_STATE::HOLD)
		{
			this->TF->MinusCount();
		}
		monsterState = MONSTER_STATE::DEAD;
		//SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
	}

	// 2. �����Ϳ� �浹���� ��
	if (_other->GetName() == "Supporter")
	{
		Supporter* supporter = dynamic_cast<Supporter*>(_other);
		assert(supporter && "cannot find supporter\n");
		SUPPORTER_STATE otherSupporterState = supporter->GetGameState();

		// 2-1. �����Ͱ� MOVE ������ �� && (���Ͱ� MOVE ������ �� || ���Ͱ� IDLE ������ ��)
		// -> ���� ���� HOLD�� ����
		if (otherSupporterState == SUPPORTER_STATE::MOVE &&
			(monsterState == MONSTER_STATE::MOVE || monsterState == MONSTER_STATE::IDLE))
		{
			SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::FROZENMON);
			SoundManager::GetInstance()->Play(SoundManager::VOICE, SoundManager::SUPATTACK);
			monsterState = MONSTER_STATE::HOLD;
			this->TF->PlusCount();
			//if (!pastFrozen) 
			{
				this->DZ->SubZ();
			}
			this->pastFrozen = true;
			this->frozEffect->SetOnOff(true);
		}

		// 2-2. �����Ͱ� IDLE ������ �� && ���Ͱ� MOVE ������ ��
		// -> ���� ���� DEAD�� ����
		// Supporter : ������ ���� HIT / HP--
		if (otherSupporterState == SUPPORTER_STATE::IDLE &&
			monsterState == MONSTER_STATE::MOVE)
		{
			if (this->monsterState == MONSTER_STATE::HOLD)
			{
				this->TF->MinusCount();
			}
			//monsterState = MONSTER_STATE::DEAD;
		}
	}

	// 3. ���Ϳ� �浹���� ��
	if (_other->GetName() == "Monster")
	{
		Monster* monster = (Monster*)_other;
		MONSTER_STATE otherMonsterState = monster->GetGameState();

		// 3-1. ��� ���Ͱ� MOVE ������ �� && ���Ͱ� HOLD ������ ��
		// -> ���� ���� IDLE�� ����
		if (otherMonsterState == MONSTER_STATE::MOVE && monsterState == MONSTER_STATE::HOLD)
		{
			this->TF->MinusCount();

			monsterState = MONSTER_STATE::IDLE;
		}
	}

	// @@@@ ���� - ����� �浹 ���Ѵ� @@@@
	// 4. ������ �浹���� �� 
// 	if (_other->GetName() == "Guardian")
// 	{
// 		Guardian* guardian = (Guardian*)_other;
// 		GUARDIAN_STATE otherGuardianState = guardian->GetGameState();
// 
// 		// 4-1. ������� IDLE ������ �� && ���Ͱ� MOVE ����
// 		// -> ���� ���� DEAD�� ����
// 		// Guardian : ����� ���� HIT / HP--
// 		if (otherGuardianState == GUARDIAN_STATE::IDLE && 
// 			monsterState == MONSTER_STATE::MOVE)
// 		{
// 			monsterState = MONSTER_STATE::DEAD;
// 		}
// 	}

	// @@@@ �� ó���� ����� ���� �������� ���ش� @@@@
	// TODO: �ϴ� ���� ���� ��ü ���� DEAD�� ���� ��ȹ�� ���� ����
	// 5. ����� ���� ������ �浹���� ��
// 	if (_other->GetName() == "RangeGuardianAttack")
// 	{
// 		// 5-1. ���Ͱ� IDLE ������ �� && ����� ���� ���� ON
// 		// -> ���� ���� DEAD�� ����
// 		// Guardian : ����� ���� ATTACK
// 		if (monsterState == MONSTER_STATE::IDLE)
// 		{
// 			monsterState = MONSTER_STATE::DEAD;
// 		}
// 	}
}

void Monster::OnCollisionStay(Object* _other)
{

}

void Monster::OnCollisionExit(Object* _other)
{

}

// ���� ���⿡ ���� �����̱�
void Monster::UpdateMOVE(float _deltaTime)
{
	// ������ ��ų�� ����� ��� ���� ���

// 	if (dealer->GetGameState() == DEALER_STATE::ATTACK)
// 	{
// 		monsterState = MONSTER_STATE::DEAD;
// 		return;
// 	}


	// MOVE Animation

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
		monsterState = MONSTER_STATE::IDLE;
		transform->SetPosition(Grid::GetPostion(this->postionInGrid.x, this->postionInGrid.y));
	}

}

// 
void Monster::UpdateIDLE(float _deltaTime)
{
	// ������ ��ų�� ����� ��� ���� ���
	/*
	if (GetGamePlayManager()->GetDealer()->GetDealerState() == DEALER_STATE::ATTACK)
	{
		monsterState = MONSTER_STATE::DEAD;
		return;
	}
	*/

	// IDLE Animation

	// ���� �ð��� ������ -> MOVE ���·� ����
	moveElapsedTime += _deltaTime;
	if (moveElapsedTime >= OWNSTOPTIME)
	{
		moveElapsedTime = 0.0f;
		monsterState = MONSTER_STATE::MOVE;
		switch (nextDirection)
		{
			case DIRECTION::UP:
			{
				this->postionInGrid.y--;
				// MOVE�� �ٷ� ���� �̵��ϱ�
				return;
				break;
			}
			case DIRECTION::DOWN:
			{
				this->postionInGrid.y++;
				// MOVE�� �ٷ� ���� �̵��ϱ�
				return;
				break;
			}
			case DIRECTION::LEFT:
			{
				this->postionInGrid.x--;
				lookDirection = DIRECTION::LEFT;
				// MOVE�� �ٷ� ���� �̵��ϱ�
				return;
				break;
			}
			case DIRECTION::RIGHT:
			{
				this->postionInGrid.x++;
				lookDirection = DIRECTION::RIGHT;
				// MOVE�� �ٷ� ���� �̵��ϱ�
				return;
				break;
			}
			default:
				break;

		}
	}

	// ���� �̵����� ���ϱ�
	// LEFT / RIGHT / UP / DOWN
	Transform* transform = GetComponent<Transform>();

	// Dealer ��ġ Const ������ �ֱ�
	Vector2 targetPosition = { CENTER_POS_X, CENTER_POS_Y };
	Vector2 myPosition = transform->GetPosition();
	Vector2 dir = targetPosition - myPosition;

	int randValue = random::GetRandom<int>(0, 1);
	if (dir.x < 0 && dir.y > 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::LEFT;
			lookDirection = DIRECTION::LEFT;
		}
		else
		{
			nextDirection = DIRECTION::DOWN;
		}
	}

	if (dir.x > 0 && dir.y > 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::RIGHT;
			lookDirection = DIRECTION::RIGHT;
		}
		else
		{
			nextDirection = DIRECTION::DOWN;
		}
	}
	if (dir.x < 0 && dir.y < 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::LEFT;
			lookDirection = DIRECTION::LEFT;
		}
		else
		{
			nextDirection = DIRECTION::UP;
		}
	}
	if (dir.x > 0 && dir.y < 0)
	{
		if (randValue == 0)
		{
			nextDirection = DIRECTION::RIGHT;
			lookDirection = DIRECTION::RIGHT;
		}
		else
		{
			nextDirection = DIRECTION::UP;
		}
	}
}

// ���� ���̾�� �±� �� ��� �ð�
void Monster::UpdateDEAD_READY(float _deltaTime)
{
	if (getGdnHit)
	{
		getGdnHitTime += _deltaTime;
		if (getGdnHitTime >= 0.5f)
		{
			getGdnHitTime = 0.0f;
			monsterState = MONSTER_STATE::DEAD;
			//SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
			getGdnHit = false;
		}
		return;
	}
	deadReadyElapsedTime += _deltaTime;
	if (deadReadyElapsedTime >= DEAD_FIREBALL_READYTIME)
	{
		deadReadyElapsedTime = 0.0f;
		monsterState = MONSTER_STATE::DEAD;
		//SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
	}

}

void Monster::UpdateHOLD_DEAD_READY(float _deltaTime)
{
	getGdnHitTime += _deltaTime;
	if (getGdnHitTime >= 0.5f)
	{
		getGdnHitTime = 0.0f;
		monsterState = MONSTER_STATE::DEAD;
		//SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
		getGdnHit = false;
	}
}

void Monster::UpdateDEAD(float _deltaTime)
{
	// DEAD Animation

	// ������ ��ų�� ����� ��� ���� ���
	/*

	*/

	// DEAD Animation ����� ���ؼ� DEAE ���� �����ϱ�
	deadElapsedTime += _deltaTime;
	if (deadElapsedTime >= DEADTIME)
	{
		deadElapsedTime = 0.0f;
		// �ٽ� Ǯ�� ���ư���
		monsterState = MONSTER_STATE::IDLE;
		monsterPool->ReleaseObject(this);
		this->SetState(OBJECT_STATE::DEAD);
		this->frozEffect->SetState(OBJECT_STATE::DEAD);
		this->gdnAtkEft->SetState(OBJECT_STATE::DEAD);
		//SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
	}
}

void Monster::UpdateHOLD(float _deltaTime)
{
	// HOLD Animation

	// ���� ������ ����
	nextDirection = DIRECTION::NONE;

	// ������ ��ų�� ����� ��� ���� ���
// 	if (dealer->GetGameState() == DEALER_STATE::ATTACK)
// 	{
// 		monsterState = MONSTER_STATE::DEAD;
// 	}


	// ������� ���ݿ� ���� ���
	/*
	if(GetGamePlayManager()->GetGuardian()->GetGuardianState() == GUARDIAN_STATE::ATTACK)
	{
		monsterState = MONSTER_STATE::DEAD;
	}
	*/
}


