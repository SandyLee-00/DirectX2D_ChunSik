#include "Dealer.h"
#include "ManagerSet.h"
#include "BarDealerZ.h"
#include "RangeSupporterSheild.h"
#include "ShieldToDealer.h"
#include "Monster.h"

Dealer::Dealer(ManagerSet* _managers)
	: Object("Dealer", _managers, OBJECT_TYPE::DEALER, { 902, 441 })
	, dealerState(DEALER_STATE::IDLE)
	, HP(this->MAXHP)
	, cutSceneTime(0)
	, animation(nullptr)
	, isSupShield(false)
	, shieldTime(0.f)
	, supporterShield(nullptr)
	, hpBar(nullptr)
	, zBar(nullptr)
	, attackRange(nullptr)
	, attackElapsedTime(0.f)
	, getHitElapsedTime(0.f)
	, deadAniElapsedTime(0.f)
	, isDead(false)
	, lastAttack(false)
{

}

Dealer::~Dealer()
{
}

void Dealer::Start()
{
	this->dealerState = DEALER_STATE::IDLE;

	auto collider = CreateComponent<BoxCollider>();
	collider->SetSize(100, 50);
	this->GetManagers()->GetCollisionManager()->AddCollider(collider);

	CreateComponent<Animation>();
	animation = GetComponent<Animation>();
	animation->SetOffset({ 0, -50 });
	animation->SetSpriteRes(0, L"a", "a", 0, 0);
}

void Dealer::Update(float _deltaTime)
{
	switch (this->dealerState)
	{
		case DEALER_STATE::IDLE:
			UpdateIDLE(_deltaTime);
			break;
		case DEALER_STATE::ATTACK:
			UpdateATTACK(_deltaTime);
			break;
		case DEALER_STATE::HIT:
			UpdateHIT(_deltaTime);
			break;
		case DEALER_STATE::PROTECTED:
			UpdatePROTECTED(_deltaTime);
			break;
		case DEALER_STATE::DEAD:
			UpdateDEAD(_deltaTime);
			break;
		case DEALER_STATE::END:
			break;
		default:
			break;
	}

	shieldTime -= _deltaTime;
	if (shieldTime <= 0)
	{
		this->isSupShield = false;
	}
}

void Dealer::UpdateIDLE(float _deltaTime)
{
	if (zBar->GetZ() <= 0 && this->GetManagers()->GetKeyManager()->GetKeyState(KEY::LSHIFT) == KEY_STATE::DOWN)
	{
		SoundManager::GetInstance()->Play(SoundManager::DEALEREFFECT, SoundManager::DEALVOICE);
		this->dealerState = DEALER_STATE::ATTACK;
	}
}

void Dealer::UpdateATTACK(float _deltaTime)
{
	// SoundManager::GetInstance()->Play(SoundManager::DEALEREFFECT, SoundManager::DEALSKILLATCK);

	// ATTACK 애니메이션 재생 시간
	attackElapsedTime += _deltaTime;
	if (lastAttack)
	{
		if (attackElapsedTime >= 25.f)
		{
			attackElapsedTime = 0.f;
			this->dealerState = DEALER_STATE::IDLE;
			this->cutSceneTime = 0.0f;
		}
	}
	else
	{
		if (attackElapsedTime >= ATTACKTIME)
		{
			attackElapsedTime = 0.f;
			this->dealerState = DEALER_STATE::IDLE;
			this->cutSceneTime = 0.0f;
		}
	}
}

void Dealer::UpdateHIT(float _deltaTime)
{
	// TODO 딜러 피격 사운드 
	UpdateIDLE(_deltaTime);

	this->getHitElapsedTime += _deltaTime;
	if (this->getHitElapsedTime >= this->HIT_EFFECTTIME)
	{
		this->getHitElapsedTime = 0.f;
		if (this->HP <= 0)
		{
			UpdateDEAD(_deltaTime);
			this->dealerState = DEALER_STATE::DEAD;
			return;
		}

		this->dealerState = DEALER_STATE::IDLE;
	}
}

void Dealer::UpdatePROTECTED(float _deltaTime)
{
	this->shieldTime += _deltaTime;
	if (shieldTime >= SUPPORTER_SHIELD_MAXTIME)
	{
		this->shieldTime = 0.f;
		this->dealerState = DEALER_STATE::IDLE;
		this->supporterShield->SetOnOff(false);
	}
}

void Dealer::UpdateDEAD(float _deltaTime)
{
	this->deadAniElapsedTime += _deltaTime;
	if (this->deadAniElapsedTime >= 1.8f)
	{
		this->isDead = true;
		this->deadAniElapsedTime = 0.f;
	}

}

void Dealer::Render(GraphicsEngine* _graphicsEngine)
{
	switch (this->dealerState)
	{
		case DEALER_STATE::IDLE:
			animation->SetSpriteRes(15, L"Animation\\Deal\\DealIdle.txt", "DealerIdle", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			break;
		case DEALER_STATE::ATTACK:
			animation->SetSpriteRes(17, L"Animation\\Deal\\DealSkill.txt", "DealerSkill", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			break;
		case DEALER_STATE::HIT:
			animation->SetSpriteRes(16, L"Animation\\Deal\\DealGetHit.txt", "DealerGetHit", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			break;
		case DEALER_STATE::DEAD:
			animation->SetSpriteRes(50, L"Animation\\Deal\\DealDeath.txt", "DealerDeath", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			if (isDead)
			{
				animation->SetSpriteRes(65, L"Animation\\Deal\\DealDead.txt", "DealerDeath", (int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y);
			}
			break;
		case DEALER_STATE::PROTECTED:
			this->supporterShield->Render(_graphicsEngine);
			break;
		case DEALER_STATE::END:
			break;
		default:
			break;
	}
}

void Dealer::DebugRender(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = this->GetComponent<Transform>()->GetPosition();
	std::string stateString = "Dealer";

	// state에 따라 update 하기
	if (dealerState == DEALER_STATE::IDLE)
	{
		stateString += " IDLE";
	}
	else if (dealerState == DEALER_STATE::ATTACK)
	{
		stateString += " ATTACK";
	}

	if (this->isSupShield)
	{
		//_graphicsEngine->DrawRectangle((int)GetComponent<Transform>()->GetPosition().x, (int)GetComponent<Transform>()->GetPosition().y ,20, 20);
	}

	stateString += "\nHP: " + std::to_string(HP);

	_graphicsEngine->DrawString((int)position.x, (int)position.y, stateString);
}

void Dealer::OnCollisionEnter(Object* _other)
{

	//if (this->dealerState == DEALER_STATE::IDLE && _other->GetName() == "Monster" && !isSupShield)
	//{
	//	HP--;
	//	if (HP <= 0) 
	//	{
	//		// dead
	//	}
	//}

	// 1. 몬스터와 충돌했을 때
	if (_other->GetName() == "Monster")
	{
		Monster* monster = dynamic_cast<Monster*>(_other);
		MONSTER_STATE monsterState = monster->GetGameState();
		// 1-1. 현재 상태가 IDLE 상태일 때 && Shield가 없을 때
		// -> HP 감소
		if (this->dealerState == DEALER_STATE::IDLE &&
			isSupShield == false)
		{
			SoundManager::GetInstance()->Play(SoundManager::DEALEREFFECT, SoundManager::DEALHIT);
			HP -= HP_DEC;
			this->dealerState = DEALER_STATE::HIT;
			SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
			monster->SetGameState(MONSTER_STATE::DEAD);
		}

		// 1-2. IDLE 상태일 때 && Shield가 있을 때
		if (this->dealerState == DEALER_STATE::IDLE &&
			isSupShield == true)
		{
			isSupShield = false;
			//to do: 무적시간 주기
			HP -= HP_DEC_SHIELD;
			this->dealerState = DEALER_STATE::PROTECTED;
		}
	}

}

void Dealer::OnCollisionStay(Object* _other)
{
	if (_other->GetName() == "RangeSupporterSheild")
	{
		RangeSupporterSheild* rSS = dynamic_cast<RangeSupporterSheild*>(_other);
		if (rSS->GetOnOff())
		{
			this->supporterShield->SetOnOff(true);
			this->isSupShield = true;
			this->shieldTime = 4;
		}

	}

}

void Dealer::OnCollisionExit(Object* _other)
{

}
