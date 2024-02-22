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

// TODO: this->GetManagers()->GetCollisionManager()->AddCollider(collider); 이부분에서 터진다
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
	// state에 따라 update 하기
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

	// 점수 이펙트 isScoreOn 되면 정해진 시간 지나고 Off 하기
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

	// state에 따라 render 하기
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
			// DEAD_READY에서는 IDLE
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
			// DEAD_READY에서는 IDLE
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
			// DEAD_READY에서는 IDLE
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
			// DEAD_READY에서는 IDLE
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

	// 몬스터 점수 isScoreOn 되면 그리기
	// __________________________________
	const int OFFSET_X = 20;
	const int OFFSET_Y = -30;

	if (isScoreOn == true)
	{
		// 그리기 전 펜 설정
		_graphicsEngine->ChangeFontSize(25.f);
		_graphicsEngine->ColorSet(D2D1::ColorF::White);

		// 점수 그리기
		std::string scoreString = "";
		scoreString += "+ ";
		scoreString += std::to_string(this->eachMonsterScore);

		_graphicsEngine->DrawString((int)position.x + OFFSET_X, (int)position.y + OFFSET_Y, scoreString);

		// 그린 후 펜 되돌리기
		_graphicsEngine->ColorSet(D2D1::ColorF::Black);
		_graphicsEngine->ChangeFontSize(12.f);
	}
}

void Monster::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Monster";

	// state에 따라 update 하기
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

	// 몬스터가 MOVE 일 때 부딪힌 오브젝트가 딜러인 경우
	if (monsterState == MONSTER_STATE::MOVE &&
		_collision->collider1->GetOwner()->GetName() == "Dealer")
	{
		monsterState = MONSTER_STATE::DEAD;
	}

	*/

	// 1. 딜러와 충돌했을 때
	// -> 내 상태 DEAD로 변경
	// Dealer : 딜러 상태 HIT / HP--
	if (_other->GetName() == "Dealer")
	{
		if (this->monsterState == MONSTER_STATE::HOLD)
		{
			this->TF->MinusCount();
		}
		monsterState = MONSTER_STATE::DEAD;
		//SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
	}

	// 2. 서포터와 충돌했을 때
	if (_other->GetName() == "Supporter")
	{
		Supporter* supporter = dynamic_cast<Supporter*>(_other);
		assert(supporter && "cannot find supporter\n");
		SUPPORTER_STATE otherSupporterState = supporter->GetGameState();

		// 2-1. 서포터가 MOVE 상태일 때 && (몬스터가 MOVE 상태일 때 || 몬스터가 IDLE 상태일 때)
		// -> 몬스터 상태 HOLD로 변경
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

		// 2-2. 서포터가 IDLE 상태일 때 && 몬스터가 MOVE 상태일 때
		// -> 몬스터 상태 DEAD로 변경
		// Supporter : 서포터 상태 HIT / HP--
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

	// 3. 몬스터와 충돌했을 때
	if (_other->GetName() == "Monster")
	{
		Monster* monster = (Monster*)_other;
		MONSTER_STATE otherMonsterState = monster->GetGameState();

		// 3-1. 상대 몬스터가 MOVE 상태일 때 && 몬스터가 HOLD 상태일 때
		// -> 몬스터 상태 IDLE로 변경
		if (otherMonsterState == MONSTER_STATE::MOVE && monsterState == MONSTER_STATE::HOLD)
		{
			this->TF->MinusCount();

			monsterState = MONSTER_STATE::IDLE;
		}
	}

	// @@@@ 몬스터 - 가디언 충돌 안한다 @@@@
	// 4. 가디언과 충돌했을 때 
// 	if (_other->GetName() == "Guardian")
// 	{
// 		Guardian* guardian = (Guardian*)_other;
// 		GUARDIAN_STATE otherGuardianState = guardian->GetGameState();
// 
// 		// 4-1. 가디언이 IDLE 상태일 때 && 몬스터가 MOVE 상태
// 		// -> 몬스터 상태 DEAD로 변경
// 		// Guardian : 가디언 상태 HIT / HP--
// 		if (otherGuardianState == GUARDIAN_STATE::IDLE && 
// 			monsterState == MONSTER_STATE::MOVE)
// 		{
// 			monsterState = MONSTER_STATE::DEAD;
// 		}
// 	}

	// @@@@ 이 처리는 가디언 공격 범위에서 해준다 @@@@
	// TODO: 일단 공격 범위 전체 몬스터 DEAD로 변경 기획에 따라 수정
	// 5. 가디언 공격 범위와 충돌했을 때
// 	if (_other->GetName() == "RangeGuardianAttack")
// 	{
// 		// 5-1. 몬스터가 IDLE 상태일 때 && 가디언 공격 범위 ON
// 		// -> 몬스터 상태 DEAD로 변경
// 		// Guardian : 가디언 상태 ATTACK
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

// 다음 방향에 따라 움직이기
void Monster::UpdateMOVE(float _deltaTime)
{
	// 딜러가 스킬을 사용한 경우 점수 계산

// 	if (dealer->GetGameState() == DEALER_STATE::ATTACK)
// 	{
// 		monsterState = MONSTER_STATE::DEAD;
// 		return;
// 	}


	// MOVE Animation

	// 타겟, 내 위치 업데이트
	Transform* transform = GetComponent<Transform>();

	// 다음 이동방향에 따라 이동하기
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

	// 이동거리가 일정거리 이상이면 IDLE 상태로 변경

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
	// 딜러가 스킬을 사용한 경우 점수 계산
	/*
	if (GetGamePlayManager()->GetDealer()->GetDealerState() == DEALER_STATE::ATTACK)
	{
		monsterState = MONSTER_STATE::DEAD;
		return;
	}
	*/

	// IDLE Animation

	// 일정 시간이 지나면 -> MOVE 상태로 변경
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
				// MOVE로 바로 가서 이동하기
				return;
				break;
			}
			case DIRECTION::DOWN:
			{
				this->postionInGrid.y++;
				// MOVE로 바로 가서 이동하기
				return;
				break;
			}
			case DIRECTION::LEFT:
			{
				this->postionInGrid.x--;
				lookDirection = DIRECTION::LEFT;
				// MOVE로 바로 가서 이동하기
				return;
				break;
			}
			case DIRECTION::RIGHT:
			{
				this->postionInGrid.x++;
				lookDirection = DIRECTION::RIGHT;
				// MOVE로 바로 가서 이동하기
				return;
				break;
			}
			default:
				break;

		}
	}

	// 다음 이동방향 정하기
	// LEFT / RIGHT / UP / DOWN
	Transform* transform = GetComponent<Transform>();

	// Dealer 위치 Const 값으로 넣기
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

// 몬스터 파이어볼에 맞기 전 대기 시간
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

	// 딜러가 스킬을 사용한 경우 점수 계산
	/*

	*/

	// DEAD Animation 재생을 위해서 DEAE 상태 유지하기
	deadElapsedTime += _deltaTime;
	if (deadElapsedTime >= DEADTIME)
	{
		deadElapsedTime = 0.0f;
		// 다시 풀로 돌아가기
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

	// 다음 움직임 없음
	nextDirection = DIRECTION::NONE;

	// 딜러가 스킬을 사용한 경우 점수 계산
// 	if (dealer->GetGameState() == DEALER_STATE::ATTACK)
// 	{
// 		monsterState = MONSTER_STATE::DEAD;
// 	}


	// 가디언의 공격에 맞은 경우
	/*
	if(GetGamePlayManager()->GetGuardian()->GetGuardianState() == GUARDIAN_STATE::ATTACK)
	{
		monsterState = MONSTER_STATE::DEAD;
	}
	*/
}


