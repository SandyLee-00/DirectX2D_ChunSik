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

	// 가디언 공격범위 쿨타임시간 업데이트
	elapsedAttackReadyTime += _deltaTime;

	// 서포터 실드 걸었을때 시간 줄이는 코드
	supporterShieldElapsedTime -= _deltaTime;
	if (supporterShieldElapsedTime <= 0.f)
	{
		SetSupShield(false);
		this->supporterShieldElapsedTime = GURDIAN_SHIELD_MAXTIME;
	}

	// 가디언 실드 쿨타임
	// 차는 것으로 설정
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
	// TODO: 가디언 공격에 대한 애니메이션 리소스 받아서 넣기
	// 
	if (guardianState == GUARDIAN_STATE::IDLE)
	{
		//나중에 확인
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
	// 가디언이 공격할 때
	else if (guardianState == GUARDIAN_STATE::ATTACK)
	{
		// 왼쪽 볼 때
		if (this->lookDirection == DIRECTION::LEFT)
		{
			animation->SetSpriteRes(77, L"Animation\\Gdn\\GdnAtkL.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y - 30);
		}
		// 오른쪽 볼 때
		else if (this->lookDirection == DIRECTION::RIGHT)
		{
			animation->SetSpriteRes(78, L"Animation\\Gdn\\GdnAtkR.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y - 30);
		}

	}

	// 가디언이 맞았을 때
	else if (guardianState == GUARDIAN_STATE::HIT)
	{
		// 왼쪽 볼 때
		if (this->lookDirection == DIRECTION::LEFT)
		{
			animation->SetSpriteRes(59, L"Animation\\Gdn\\GdnGetHitLeft.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}
		// 오른쪽 볼 때
		else if (this->lookDirection == DIRECTION::RIGHT)
		{
			animation->SetSpriteRes(60, L"Animation\\Gdn\\GdnGetHitRight.txt", "nullptr", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
		}

	}
	// 가디언이 죽었을 때
	else if (guardianState == GUARDIAN_STATE::DEAD)
	{
		// 왼쪽 볼 때
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
		// 오른쪽 볼 때
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

	// 가디언 체력바 5칸 그리기
	//가디언이 스킬바를 그릴건데, 6초에 한번씩 다음으로 그릴생각이다. 
	float TIMEGAP = GURDIAN_SHIELD_COOLTIME / (float)GURDIAN_SHIELD_BAR_MAX;
	shieldCoolTimeBarValue = (int)(shieldCoolTime / TIMEGAP);
	//shieldCoolTimeBarValue = (int)(shieldCoolTime / 5);

	// 그려주는 부분 BackGroundOver에 그리게 위치 이동했다 

	if (this->isSupporterShield)
	{
		this->supporterShield->Render(_graphicsEngine);
	}
}

void Guardian::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Guardian";

	// state에 따라 update 하기
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
			// TODO: 가디언 실드 시간 맞는지 확인하기
			supporterShieldElapsedTime = this->GURDIAN_SHIELD_MAXTIME;
		}

	}
}


void Guardian::OnCollisionExit(Object* _other)
{

}

// 이동방향 가도 되는지 체크하기 -> 이동방향 정하기 -> 이동하기

void Guardian::UpdateIDLE(float _deltaTime)
{
	// IDLE Animation

	// 다음 이동방향 정하기
	// LEFT / RIGHT / UP / DOWN
	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();
	Vector2 targetPosition;

	// 	if (targetMonster != nullptr)
	// 	{
	// 		targetPosition = targetMonster->GetComponent<Transform>()->GetPosition();
	// 		// Monster DEAD 상태면 
	// 		// -> IDLE 상태로 변경 X
	// 		// -> 타겟 찾기
	// 		if (targetMonster->GetGameState() == MONSTER_STATE::DEAD)
	// 		{
	// 			OutputDebugString(L"work\n");
	// 			targetMonster = nullptr;
	// 			// FindTargetMonster();
	// 
	// 			return;
	// 		}
	// 	}
	// 	// 타겟 없으면 서포터 쫒아가기 
	// 	else if (targetMonster == nullptr)
	// 	{
	// 		targetPosition = supporter->GetComponent<Transform>()->GetPosition();
	// 		//targetPosition = Vector2(CENTER_POS_X, CENTER_POS_Y);
	// 	}

		/// @@@ 가디언 나가서 무조건 서포터만 따라다니게 하기 @@@
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

	// 일정 시간이 지나면 -> MOVE 상태로 변경
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
		guardianState = GUARDIAN_STATE::IDLE;
		transform->SetPosition(Grid::GetPostion(this->postionInGrid.x, this->postionInGrid.y));
	}
}

// 몬스터 1초동안 때리고 RangeGuardian 활성화
void Guardian::UpdateATTACK(float _deltaTime)
{
	// ATTACKTIME 지나면
	// -> 가디언 상태 IDLE로 바꾸기
	// -> 가디언 공격 범위 OFF
	// -> 공격 범위 쿨타임 초기화
	elapsedAttackTime += _deltaTime;
	if (elapsedAttackTime >= ATTACKTIME)
	{
		elapsedAttackTime = 0.0f;
		guardianState = GUARDIAN_STATE::IDLE;
		//attackRange->SetOnOff(false);
		elapsedAttackReadyTime = 0.0f;
		return;
	}

	// @@@@TargetMonster null 체크 꼭 하기 @@@@
	// 타겟이 없으면
	// -> IDLE 상태로 변경 X
	// -> 타겟 찾기
	if (targetMonster == nullptr)
	{
		// FindTargetMonster();
		return;
	}

	// Monster DEAD 상태면 
	// -> IDLE 상태로 변경 X
	// -> 타겟 찾기
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
	// 현재 씬에 Add 된 OBJECT_TYPE::MONSTER 갖고오기
	Scene* currentScene = this->GetManagers()->GetSceneManager()->GetCurrentScene();
	std::list<Object*>& objList = currentScene->GetObjectListType((int)(OBJECT_TYPE::MONSTER));

	for (auto obj : objList)
	{
		Monster* monster = dynamic_cast<Monster*>(obj);
		assert(monster != nullptr && "Wrong type. expended Monster but something different");
		Vector2 monsterPos = monster->GetComponent<Transform>()->GetPosition();

		bool isInside = false;

		// 몬스터가 화면 안에 있으면 true
		if (monsterPos.x > LIMIT_X_MIN && monsterPos.x < LIMIT_X_MAX &&
			monsterPos.y > LIMIT_Y_MIN && monsterPos.y < LIMIT_Y_MAX)
		{
			isInside = true;
		}

		// 몬스터 IDLE / MOVE / HOLD 상태일 때  && 화면 안에 있으면
		// -> 가디언의 타겟으로 설정
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

// 다음번에 갈 영역이 가능한지 체크
bool Guardian::CheckMoveable(float _x, float _y)
{
	// 화면 밖으로 나가면 X
	if (_x < LIMIT_X_MIN || _x > LIMIT_X_MAX ||
		_y < LIMIT_Y_MIN || _y > LIMIT_Y_MAX)
	{
		return false;
	}

	// 딜러 영역에 들어가면 X
	if (_x > LIMIT_X_DEALER_MIN && _x < LIMIT_X_DEALER_MAX &&
		_y > LIMIT_Y_DEALER_MIN && _y < LIMIT_Y_DEALER_MAX)
	{
		return false;
	}

	return true;
}

