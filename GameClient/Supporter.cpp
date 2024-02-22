#include "Supporter.h"
#include "Monster.h"
#include "Guardian.h"
#include "Dealer.h"
#include "Grid.h"
#include "RangeSupporterSheild.h"
#include "ShieldToDealer.h"
#include "EffectSupporterMove.h"

Supporter::Supporter(ManagerSet* _managers)
	: Object("Supporter", _managers, OBJECT_TYPE::SUPPORTER, { 0, 0 })

	, currentState(SUPPORTER_STATE::IDLE)
	, previousState(SUPPORTER_STATE::IDLE)

	, nextDirection(DIRECTION::NONE)
	, lookDirection(DIRECTION::RIGHT)

	, HP(this->MAXHP)
	, hitElapsedTime(0.0f)

	, isMove(false)
	, elapsedDistance(0.0f)
	, moveSpeed(GRID_SIZE / this->MOVETIME)
	, positionInGrid{ 9, 5 }
	, elapedmoveDelayTime(0.f)

	, shieldCoolTime(0.f)
	, shieldCoolTimeBarValue(SUPPORTER_SHIELD_BAR_MAX)
	, isShieldReady(true)
	, supporterSheildRange(nullptr)
	, shieldElapsedTime(0.f)

	, animation(nullptr)
	, deadAniElapsedTime(0.f)
	, isDead(false)
	, frozEffect(nullptr)
	, supMoveEft(nullptr)
{

}

Supporter::~Supporter()
{

}

void Supporter::Start()
{
	auto transfrom = GetComponent<Transform>();
	//transfrom->SetPosition({ 854.f, 570.f });
	transfrom->SetPosition(Grid::GetPostion(this->positionInGrid.x, this->positionInGrid.y));

	auto collider = CreateComponent<BoxCollider>();
	collider->SetOffset({ 48 - 25, 48 - 25 });
	collider->SetSize({ 50, 50 });
	this->GetManagers()->GetCollisionManager()->AddCollider(collider);

	CreateComponent<Animation>();
	animation = GetComponent<Animation>();
	animation->SetOffset(Vector2{ -10, -30 });
	animation->SetSpriteRes(7, L"Animation\\Sup\\SupIdle.txt", "playerIdle2", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
}

// �Է��� dir ��� �ð� �Ǹ� �����̱�
void Supporter::Update(float _deltaTime)
{
	if (currentState == SUPPORTER_STATE::IDLE)
	{
		UpdateIDLE(_deltaTime);
	}
	else if (currentState == SUPPORTER_STATE::MOVE)
	{
		UpdateMOVE(_deltaTime);
	}
	else if (currentState == SUPPORTER_STATE::HIT)
	{
		UpdateHIT(_deltaTime);
	}
	else if (currentState == SUPPORTER_STATE::HOLD)
	{
		UpdateHOLD(_deltaTime);
	}
	else if (currentState == SUPPORTER_STATE::SHIELD)
	{
		UpdateSHIELD(_deltaTime);
	}
	else if (currentState == SUPPORTER_STATE::DEAD)
	{
		UpdateDEAD(_deltaTime);
	}

	// ����� �ǵ� ��Ÿ��
	// ���� ������ ����
	if (!isShieldReady)
	{
		shieldCoolTime += _deltaTime;
		if (shieldCoolTime >= SUPPORTERSHIELD_COOLTIME)
		{
			isShieldReady = true;
			shieldCoolTime = 0.f;
		}
	}
}

void Supporter::FinalUpdate(float _deltaTime)
{

}

void Supporter::Render(GraphicsEngine* _graphicsEngine)
{
	if (lookDirection == DIRECTION::LEFT)
	{
		if (currentState == SUPPORTER_STATE::IDLE)
		{
			//_graphicsEngine->DrawSprite("playeridle", 0, GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y, 50, 50);
			animation->SetSpriteRes(7, L"Animation\\Sup\\SupIdleLeft.txt", "playerIdle", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			//temp2->SetSpriteRes(8, L"Animation\\Sup\\SupMove.txt", "playerMove", GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::MOVE || currentState == SUPPORTER_STATE::HOLD)
		{
			animation->SetSpriteRes(9, L"Animation\\Sup\\SupMoveLeft.txt", "playerMove", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::HIT)
		{
			animation->SetSpriteRes(11, L"Animation\\Sup\\SupGetHitLeft.txt", "playerHit", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::SHIELD)
		{
			animation->SetSpriteRes(13, L"Animation\\Sup\\SupShieldLeft.txt", "playersld", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::DEAD)
		{
			animation->SetSpriteRes(61, L"Animation\\Sup\\SupDeathL.txt", "playerdeathL", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			if (isDead)
			{
				animation->SetSpriteRes(63, L"Animation\\Sup\\SupDeadL.txt", "playerdeathR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}
	}
	else if (lookDirection == DIRECTION::RIGHT)
	{
		if (currentState == SUPPORTER_STATE::IDLE)
		{
			//_graphicsEngine->DrawSprite("playeridle", 0, GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y, 50, 50);
			animation->SetSpriteRes(8, L"Animation\\Sup\\SupIdleRight.txt", "playerIdle1", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			//temp2->SetSpriteRes(8, L"Animation\\Sup\\SupMove.txt", "playerMove", GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::MOVE || currentState == SUPPORTER_STATE::HOLD)
		{
			animation->SetSpriteRes(10, L"Animation\\Sup\\SupMoveRight.txt", "playerMove1", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::HIT)
		{
			animation->SetSpriteRes(12, L"Animation\\Sup\\SupGetHitRight.txt", "playerHit1", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::SHIELD)
		{
			animation->SetSpriteRes(14, L"Animation\\Sup\\SupShieldRight.txt", "playersld1", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		else if (currentState == SUPPORTER_STATE::DEAD)
		{
			animation->SetSpriteRes(62, L"Animation\\Sup\\SupDeathR.txt", "playerdeathR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			if (isDead)
			{
				animation->SetSpriteRes(64, L"Animation\\Sup\\SupDeadR.txt", "playerdeathR", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
		}
	}

	// ������ �ǵ�� 5ĭ �׸���
	float TIMEGAP = SUPPORTERSHIELD_COOLTIME / (float)SUPPORTER_SHIELD_BAR_MAX;
	shieldCoolTimeBarValue = (int)(shieldCoolTime / TIMEGAP);

}

void Supporter::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Supporter";

	// state�� ���� update �ϱ�
	if (currentState == SUPPORTER_STATE::IDLE)
	{
		stateString += " IDLE";
	}
	else if (currentState == SUPPORTER_STATE::MOVE)
	{
		stateString += " MOVE";
	}
	else if (currentState == SUPPORTER_STATE::HIT)
	{
		stateString += " HIT";
	}

	stateString += "\nHP: " + std::to_string(HP);

	_graphicsEngine->DrawString((int)position.x, (int)position.y, stateString);
}

void Supporter::OnCollisionEnter(Object* _other)
{
	// 1. ���Ϳ� �浹���� ��
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		MONSTER_STATE monsterState = monster->GetGameState();

		// 1-2. �����Ͱ� IDLE ������ �� && ���Ͱ� MOVE ������ ��
		// Monster : ���� ���� DEAD�� ����
		// -> ������ ���� HIT���� ���� / HP--
		if (currentState == SUPPORTER_STATE::IDLE &&
			monsterState == MONSTER_STATE::MOVE)
		{
			currentState = SUPPORTER_STATE::HIT;
			SoundManager::GetInstance()->Play(SoundManager::VOICE, SoundManager::SUPHIT);
			SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
			monster->SetGameState(MONSTER_STATE::DEAD);
			// HP ����
			HP -= HP_DEC;
		}
	}

}

void Supporter::OnCollisionStay(Object* _other)
{

}

void Supporter::OnCollisionExit(Object* _other)
{

}

// �������� �� ������ �������� üũ
bool Supporter::CheckMoveable(float _x, float _y)
{
	// ȭ�� ������ ������ X
	if (_x < LIMIT_X_MIN || _x > LIMIT_X_MAX ||
		_y < LIMIT_Y_MIN || _y > LIMIT_Y_MAX)
	{
		return false;
	}

	// ���� ������ ���� X
// 	if (_x > LIMIT_X_DEALER_MIN && _x < LIMIT_X_DEALER_MAX &&
// 		_y > LIMIT_Y_DEALER_MIN && _y < LIMIT_Y_DEALER_MAX)
// 	{
// 		return false;
// 	}

	return true;
}

// Ű���� �Է� ������ IDLE -> MOVE
void Supporter::UpdateIDLE(float _deltaTime)
{
	KeyManager* keyManager = this->GetManagers()->GetKeyManager();
	Transform* tranform = this->GetComponent<Transform>();
	Vector2 position = tranform->GetPosition();

	// SPACE ������ SHEILD
	if (keyManager->GetKeyState(KEY::SPACE) == KEY_STATE::DOWN && isShieldReady == true)
	{
		SoundManager::GetInstance()->Play(SoundManager::VOICE, SoundManager::SUPSHIED);
		currentState = SUPPORTER_STATE::SHIELD;
		supporterSheildRange->SetOnOff(true);
		isShieldReady = false;
		return;
	}

	// �����¿� Ű ������ MOVE
	// ������ ��Ÿ���� �� �� �� �ֵ���
	if (keyManager->GetKeyState(KEY::LEFT) == KEY_STATE::DOWN && CheckMoveable(position.x - LIMIT_GOINSIDE_GAP, position.y))
	{
		nextDirection = DIRECTION::LEFT;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.x--;
		lookDirection = DIRECTION::LEFT;
		this->supMoveEft->SetOnOff(true);
	}
	else if (keyManager->GetKeyState(KEY::RIGHT) == KEY_STATE::DOWN && CheckMoveable(position.x + LIMIT_GOINSIDE_GAP, position.y))
	{
		nextDirection = DIRECTION::RIGHT;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.x++;
		lookDirection = DIRECTION::RIGHT;
		this->supMoveEft->SetOnOff(true);
	}
	else if (keyManager->GetKeyState(KEY::UP) == KEY_STATE::DOWN && CheckMoveable(position.x, position.y - LIMIT_GOINSIDE_GAP))
	{
		nextDirection = DIRECTION::UP;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.y--;
		this->supMoveEft->SetOnOff(true);
	}
	else if (keyManager->GetKeyState(KEY::DOWN) == KEY_STATE::DOWN && CheckMoveable(position.x, position.y + LIMIT_GOINSIDE_GAP))
	{
		nextDirection = DIRECTION::DOWN;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.y++;
		this->supMoveEft->SetOnOff(true);
	}

	// Ű �� ������ �� ������ �ֱ�
	// �׸��� �����ŭ ���� IDLE�� ���ͼ� MOVE_DELAY �ֱ�
	elapedmoveDelayTime += _deltaTime;
	// MOVE_DELAY��ŭ IDLE ����
	if (elapedmoveDelayTime >= MOVE_DELAY)
	{
		elapedmoveDelayTime = 0.f;
	}
	else
	{
		// �ڿ� �̵� �ڵ� �����ϱ�
		return;
	}

	this->isMove = false;

	// �����¿� Ű ������ MOVE
	if (keyManager->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD && CheckMoveable(position.x - LIMIT_GOINSIDE_GAP, position.y))
	{
		SoundManager::GetInstance()->Stop(SoundManager::PLAYEREFFECT);
		SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::PLAYERMOVE);
		nextDirection = DIRECTION::LEFT;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.x--;
		lookDirection = DIRECTION::LEFT;
		this->supMoveEft->SetOnOff(true);
	}
	else if (keyManager->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD && CheckMoveable(position.x + LIMIT_GOINSIDE_GAP, position.y))
	{
		SoundManager::GetInstance()->Stop(SoundManager::PLAYEREFFECT);
		SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::PLAYERMOVE);
		nextDirection = DIRECTION::RIGHT;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.x++;
		lookDirection = DIRECTION::RIGHT;
		this->supMoveEft->SetOnOff(true);
	}
	else if (keyManager->GetKeyState(KEY::UP) == KEY_STATE::HOLD && CheckMoveable(position.x, position.y - LIMIT_GOINSIDE_GAP))
	{
		SoundManager::GetInstance()->Stop(SoundManager::PLAYEREFFECT);
		SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::PLAYERMOVE);
		nextDirection = DIRECTION::UP;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.y--;
		this->supMoveEft->SetOnOff(true);
	}
	else if (keyManager->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD && CheckMoveable(position.x, position.y + LIMIT_GOINSIDE_GAP))
	{
		SoundManager::GetInstance()->Stop(SoundManager::PLAYEREFFECT);
		SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::PLAYERMOVE);
		nextDirection = DIRECTION::DOWN;
		currentState = SUPPORTER_STATE::MOVE;
		this->positionInGrid.y++;
		this->supMoveEft->SetOnOff(true);
	}
}

void Supporter::UpdateMOVE(float _deltaTime)
{

	this->isMove = true;

	// Ÿ��, �� ��ġ ������Ʈ
	Transform* transform = GetComponent<Transform>();

	// ���� �̵����⿡ ���� �̵��ϱ�
	Vector2 moveVector = { 0, 0 };

	if (this->nextDirection == DIRECTION::LEFT)
	{
		// MoveLeft
		moveVector = { -1, 0 };
	}
	else if (this->nextDirection == DIRECTION::RIGHT)
	{
		// MoveRight
		moveVector = { 1, 0 };
	}
	else if (this->nextDirection == DIRECTION::UP)
	{
		// MoveUp
		moveVector = { 0, -1 };
	}
	else if (this->nextDirection == DIRECTION::DOWN)
	{
		// MoveDown
		moveVector = { 0, 1 };
	}

	// �̵��ϱ�
	transform->Translation(moveVector * _deltaTime * moveSpeed);

	// �̵��Ÿ��� �����Ÿ� �̻��̸� IDLE ���·� ����
	elapsedDistance += _deltaTime * moveSpeed;
	if (elapsedDistance >= GRID_SIZE)
	{
		elapsedDistance = 0.0f;
		transform->SetPosition(Grid::GetPostion(this->positionInGrid.x, this->positionInGrid.y));
		currentState = SUPPORTER_STATE::IDLE;
	}

}

void Supporter::UpdateHIT(float _deltaTime)
{
	if (isMove)
	{
		UpdateMOVE(_deltaTime);
	}
	else
	{
		UpdateIDLE(_deltaTime);
	}
	// HIT Anim ���

	hitElapsedTime += _deltaTime;
	// HIT_EFFECTTIME ������ IDLE ���·� ����
	if (hitElapsedTime >= HIT_EFFECTTIME)
	{
		hitElapsedTime = 0.0f;
		if (this->HP <= 0)
		{
			UpdateDEAD(_deltaTime);
			this->currentState = SUPPORTER_STATE::DEAD;
			return;
		}
		currentState = isMove ? SUPPORTER_STATE::MOVE : SUPPORTER_STATE::IDLE;
	}
}

void Supporter::UpdateHOLD(float _deltaTime)
{
	SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::SUPATTACK);
	// HOLD Anim ���

	// IDLE ���·� ����
	currentState = isMove ? SUPPORTER_STATE::MOVE : SUPPORTER_STATE::IDLE;
}

void Supporter::UpdateSHIELD(float _deltaTime)
{
	// SHIELD Anim ���

	// SHIELD_EFFECTTIME ������ IDLE / MOVE ���·� ����
	shieldElapsedTime += _deltaTime;
	if (shieldElapsedTime >= SHIELD_EFFECTTIME)
	{
		shieldElapsedTime = 0.0f;
		supporterSheildRange->SetOnOff(false);
		currentState = SUPPORTER_STATE::IDLE;
	}
}

void Supporter::UpdateDEAD(float _deltaTime)
{
	this->deadAniElapsedTime += _deltaTime;
	if (this->deadAniElapsedTime >= 2.0f)
	{
		this->isDead = true;
		this->deadAniElapsedTime = 0.f;
	}

}

