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

// 입력한 dir 대로 시간 되면 움직이기
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

	// 가디언 실드 쿨타임
	// 차는 것으로 설정
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

	// 서포터 실드바 5칸 그리기
	float TIMEGAP = SUPPORTERSHIELD_COOLTIME / (float)SUPPORTER_SHIELD_BAR_MAX;
	shieldCoolTimeBarValue = (int)(shieldCoolTime / TIMEGAP);

}

void Supporter::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Supporter";

	// state에 따라 update 하기
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
	// 1. 몬스터와 충돌했을 때
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		MONSTER_STATE monsterState = monster->GetGameState();

		// 1-2. 서포터가 IDLE 상태일 때 && 몬스터가 MOVE 상태일 때
		// Monster : 몬스터 상태 DEAD로 변경
		// -> 서포터 상태 HIT으로 변경 / HP--
		if (currentState == SUPPORTER_STATE::IDLE &&
			monsterState == MONSTER_STATE::MOVE)
		{
			currentState = SUPPORTER_STATE::HIT;
			SoundManager::GetInstance()->Play(SoundManager::VOICE, SoundManager::SUPHIT);
			SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
			monster->SetGameState(MONSTER_STATE::DEAD);
			// HP 감소
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

// 다음번에 갈 영역이 가능한지 체크
bool Supporter::CheckMoveable(float _x, float _y)
{
	// 화면 밖으로 나가면 X
	if (_x < LIMIT_X_MIN || _x > LIMIT_X_MAX ||
		_y < LIMIT_Y_MIN || _y > LIMIT_Y_MAX)
	{
		return false;
	}

	// 딜러 영역에 들어가면 X
// 	if (_x > LIMIT_X_DEALER_MIN && _x < LIMIT_X_DEALER_MAX &&
// 		_y > LIMIT_Y_DEALER_MIN && _y < LIMIT_Y_DEALER_MAX)
// 	{
// 		return false;
// 	}

	return true;
}

// 키보드 입력 있으면 IDLE -> MOVE
void Supporter::UpdateIDLE(float _deltaTime)
{
	KeyManager* keyManager = this->GetManagers()->GetKeyManager();
	Transform* tranform = this->GetComponent<Transform>();
	Vector2 position = tranform->GetPosition();

	// SPACE 누르면 SHEILD
	if (keyManager->GetKeyState(KEY::SPACE) == KEY_STATE::DOWN && isShieldReady == true)
	{
		SoundManager::GetInstance()->Play(SoundManager::VOICE, SoundManager::SUPSHIED);
		currentState = SUPPORTER_STATE::SHIELD;
		supporterSheildRange->SetOnOff(true);
		isShieldReady = false;
		return;
	}

	// 상하좌우 키 누르면 MOVE
	// 빠르게 연타했을 때 갈 수 있도록
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

	// 키 꾹 눌렀을 때 딜레이 주기
	// 그리드 사이즈만큼 가면 IDLE로 들어와서 MOVE_DELAY 주기
	elapedmoveDelayTime += _deltaTime;
	// MOVE_DELAY만큼 IDLE 유지
	if (elapedmoveDelayTime >= MOVE_DELAY)
	{
		elapedmoveDelayTime = 0.f;
	}
	else
	{
		// 뒤에 이동 코드 무시하기
		return;
	}

	this->isMove = false;

	// 상하좌우 키 누르면 MOVE
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

	// 타겟, 내 위치 업데이트
	Transform* transform = GetComponent<Transform>();

	// 다음 이동방향에 따라 이동하기
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

	// 이동하기
	transform->Translation(moveVector * _deltaTime * moveSpeed);

	// 이동거리가 일정거리 이상이면 IDLE 상태로 변경
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
	// HIT Anim 재생

	hitElapsedTime += _deltaTime;
	// HIT_EFFECTTIME 지나면 IDLE 상태로 변경
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
	// HOLD Anim 재생

	// IDLE 상태로 변경
	currentState = isMove ? SUPPORTER_STATE::MOVE : SUPPORTER_STATE::IDLE;
}

void Supporter::UpdateSHIELD(float _deltaTime)
{
	// SHIELD Anim 재생

	// SHIELD_EFFECTTIME 지나면 IDLE / MOVE 상태로 변경
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

