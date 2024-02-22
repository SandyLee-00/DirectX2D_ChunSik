#include "MainGameScene.h"
#include "ManagerSet.h"

// Empty Object
#include "BackGroundObject.h"
#include "MonsterSpawner.h"
#include "BackGroundOver.h"

// Object
#include "Dealer.h"
#include "Guardian.h"
#include "Monster.h"
#include "Supporter.h"
#include "ObjectPool.h"

// Attach Object
#include "BarDealerZ.h"
#include "BarHP.h"

#include "RangeGuardianAttack.h"
#include "RangeSupporterSheild.h"

#include "ShieldToDealer.h"
#include "ShieldFromGuardian.h"
#include "ShieldToGuardian.h"

#include "EffectEachMonsterScore.h"
#include "EffectSupporterMove.h"
#include "EffectFireBall.h"

// UI
#include "BarDealerZ.h"
#include "BarHP.h"
#include "TextLeftTime.h"
#include "TextScore.h"
#include "TextFrozenCount.h"

//EFFECT
#include "WhiteEffect.h"

// ��ŷ�� ������ �ѱ�� ���� �߰���
#include "RankingScene.h"

#include "SoundManager.h"

/// <summary>
/// ���ھ ���ϱ� ���� ���� functor
/// </summary>
struct Compare
{
	bool operator()(const TextPersonData& _one, const TextPersonData& _two)
	{
		if (_one.GetScore() == _two.GetScore())
		{
			// ������ �ɸ� �ð� ��� ���� ��
			if (_one.GetTotalSec() == _two.GetTotalSec())
			{
				// ���� ������ �� ����� �� ������
				// ���� �����ϴ� ����� �ؿ��� �ö���� ������
				// ���⼭�� �ٲ����� �ʰ� �׳� ������

				return false;
			}
			return _one.GetTotalSec() < _two.GetTotalSec();
		}
		return _one.GetScore() < _two.GetScore();
	}
};

MainGameScene::MainGameScene(ManagerSet* _managers)
	: Scene(_managers)
	, monsterPool(nullptr)
	, managers(_managers)
	, textFrozenCount(nullptr)
	, textLeftTime(nullptr)
	, textScore(nullptr)
	, barDealerZ(nullptr)
	, cutsceneTime(0.0f)
	, dealer(nullptr)
	, supporter(nullptr)
	, guardian(nullptr)
	, isGameOver(false)
	, deadAniElapsedTime(0.f)
	, rankingScene(nullptr)
	, totalScore(0)
	, dealAniElapsedTime(0)
	, isMainEnd(false)
	, soundFlag(false)
	, isCallOnce(false)
	, soundDelay(0.0f)
{
	monsterPool = new ObjectPool<Monster, 100>(this->managers);
}

MainGameScene::~MainGameScene()
{
	// TODO: delete �ϴϱ� ������..
	delete monsterPool;
}

void MainGameScene::Enter()
{
	DeleteAllObjects();
	totalScore = 0;
	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Main, true);

	// ������ �� ������Ʈ
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("MainGameScene");
	managers->GetSceneManager()->AddObject(obj);

	// __________________________________________________________
	//monsterPool = new ObjectPool<Monster, 100>(this->managers);



	// __________________________________________________________
	// ������Ʈ
	dealer = new Dealer(this->managers);
	managers->GetSceneManager()->AddObject(dealer);

	guardian = new Guardian(this->managers);
	managers->GetSceneManager()->AddObject(guardian);

	supporter = new Supporter(this->managers);
	managers->GetSceneManager()->AddObject(supporter);

	guardian->SetTargetSupporter(supporter);


	// __________________________________________________________
	// Attach �ϴ� ������Ʈ

	// __________________________________________________________
	// ATTACHMENT �� effect�� ó���� �͵� 
	// ����� ���ݹ���
	RangeGuardianAttack* guardianAttackRange = new RangeGuardianAttack(this->managers);
	guardianAttackRange->SetParent(guardian);
	guardian->SetChild(guardianAttackRange);
	managers->GetSceneManager()->AddObject(guardianAttackRange);

	// ������ �ǵ���� 
	RangeSupporterSheild* supporterSheildRange = new RangeSupporterSheild(this->managers);
	supporterSheildRange->SetParent(supporter);
	supporter->SetRangeSupporterSheild(supporterSheildRange);
	managers->GetSceneManager()->AddObject(supporterSheildRange);

	ShieldToDealer* shieldToDealer = new ShieldToDealer(this->managers);
	shieldToDealer->SetRangeSupporterShield(supporterSheildRange);
	shieldToDealer->SetDealer(dealer);
	dealer->SetChild(shieldToDealer);
	this->managers->GetSceneManager()->AddObject(shieldToDealer);

	ShieldToGuardian* shieldToGuardian = new ShieldToGuardian(this->managers);
	shieldToGuardian->SetRangeSupporterShield(supporterSheildRange);
	shieldToGuardian->SetGuardian(guardian);
	guardian->SetChild(shieldToGuardian);
	this->managers->GetSceneManager()->AddObject(shieldToGuardian);

	supporterSheildRange->SetShieldToDealer(shieldToDealer);
	supporterSheildRange->SetShieldToGuardian(shieldToGuardian);

	EffectSupporterMove* supMoveEFt = new EffectSupporterMove(this->managers);
	supporter->SetSupMoveEft(supMoveEFt);
	supMoveEFt->SetSupporter(supporter);
	this->managers->GetSceneManager()->AddObject(supMoveEFt);

	ShieldFromGuardian* gdnShield = new ShieldFromGuardian(this->managers);
	guardian->SetChild(gdnShield);
	gdnShield->SetGuardian(guardian);
	this->managers->GetSceneManager()->AddObject(gdnShield);

	WhiteEffect* whiteEffect = new WhiteEffect(this->managers);
	whiteEffect->GetDealer(dealer);
	this->managers->GetSceneManager()->AddObject(whiteEffect);

	/*
	// ������ ���� ���� �� ��� ���� ���� ����Ʈ �������� DEAD_DELAYTIME ���Ŀ� DEAD �ȴ�
	// Ǯ�� ���̾ 100�� �����
	for (int i = 0; i < 100; i++)
	{
		EffectFireBall* effectFireBall = new EffectFireBall(this->managers);
		fireBallPool.push_back(effectFireBall);
		managers->GetSceneManager()->AddObject(effectFireBall);
	}
	*/

	// ������ ���� ���� �� ���� ���� �ߴ� ���� ������ ����
	long long tempScore = 512;

	// 1. �� ���� ���� ǥ �ʱ�ȭ�ϱ�
	for (int i = 0; i < 100; i++)
	{
		// 1 ~ 5 : 512 == 2^9
		// 6 ~ 25 : 1024 ~ 536,870,912 == 2^10 ~ 2^29
		// 26 ~ 100 : 1,000,000,000 == 10^9

		if (i <= 5)
		{
			MonsterHOLDScores.push_back(tempScore);
		}
		else if (6 <= i && i <= 25)
		{
			tempScore *= 2;
			MonsterHOLDScores.push_back(tempScore);
		}
		else if (26 <= i && i < 100)
		{
			tempScore = 1000000000;
			MonsterHOLDScores.push_back(tempScore);
		}
	}

	// 2. �� �� ���� ���� ǥ �ʱ�ȭ�ϱ�
	for (int i = 0; i < 100; i++)
	{
		MonsterXHOLDScores.push_back(100);
	}


	// __________________________________________________________
	// UI

	// ����ִ� ���� �׷��� �ϴ� �͵� - �� �� �� / HP ���� �󱼵� / HP �� ȸ���ڽ� 
	// ���ھ� �ڽ�, �ð� �ڽ�, �� �� �� �ڽ�

	BackGroundOver* backGroundOver = new BackGroundOver(this->managers);
	/*backGroundOver->SetGuardian(guardian);*/
	managers->GetSceneManager()->AddObject(backGroundOver);

	// __________________________________________________________
	// UI 

	// ���� Z 
	barDealerZ = new BarDealerZ(this->managers);
	barDealerZ->SetParent(dealer);
	dealer->SetChild(barDealerZ);
	managers->GetSceneManager()->AddObject(barDealerZ);
	barDealerZ->SetZ(barDealerZ->GetMaxZ());

	// ���� ü�� �θ��� HP ����ͼ� �����ֱ⸸ �Ѵ� 
	BarHP* barHPDealer = new BarHP(this->managers);
	barHPDealer->SetParent(dealer);
	barHPDealer->SetMaxHP(HP_DEALER_MAX);
	managers->GetSceneManager()->AddObject(barHPDealer);

	// ������ ü��
	BarHP* barHPSupporter = new BarHP(this->managers);
	barHPSupporter->SetParent(supporter);
	barHPDealer->SetMaxHP(HP_SUPPORTER_MAX);
	managers->GetSceneManager()->AddObject(barHPSupporter);

	// ����� ü��
	BarHP* barHPGuardian = new BarHP(this->managers);
	barHPGuardian->SetParent(guardian);
	barHPDealer->SetMaxHP(HP_GUARDIAN_MAX);
	managers->GetSceneManager()->AddObject(barHPGuardian);

	// ���� �� ��
	textFrozenCount = new TextFrozenCount(this->managers);
	managers->GetSceneManager()->AddObject(textFrozenCount);

	// ���� �ð�
	textLeftTime = new TextLeftTime(this->managers);
	managers->GetSceneManager()->AddObject(textLeftTime);

	// ����
	textScore = new TextScore(this->managers);
	managers->GetSceneManager()->AddObject(textScore);

	// __________________________________________________________
	// ���� ������
	MonsterSpawner* monsterSpawner = new MonsterSpawner(this->managers);
	monsterSpawner->SetName("monsterSpawner");
	monsterSpawner->SetMonsterPool(monsterPool);
	monsterSpawner->SetDZ(barDealerZ);
	monsterSpawner->SetTF(textFrozenCount);
	managers->GetSceneManager()->AddObject(monsterSpawner);

	// __________________________________________________________
	// Collision ����
	// ������ - ���� �󸮱�
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::SUPPORTER, OBJECT_TYPE::MONSTER);
	// ���Ͱ� ���� ������
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::DEALER, OBJECT_TYPE::MONSTER);
	// ���� - ���� ���� ��
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::MONSTER, OBJECT_TYPE::MONSTER);
	// ����� ���� ���� - ���� ����� ������ �ν��ϰ� ���� ������
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::MONSTER, OBJECT_TYPE::ATTACHMENT);
	// ������ �ǵ� ���� - ����
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::DEALER, OBJECT_TYPE::ATTACHMENT);
	// ������ �ǵ� ���� - �����
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::ATTACHMENT, OBJECT_TYPE::GUARDIAN);

	// ������ �ߴ���
	this->isGameOver = false;
	// ��ü ���� �ð� ����
	this->rankingScene->SetTotalPlayTime(textLeftTime->GetMAX_PLAYTIME());

	isMainEnd = false;
	dealer->LastAttack(false);

}

void MainGameScene::Exit()
{
	//delete monsterPool;

	//DeleteAllObjects();

	SoundManager::GetInstance()->Stop(SoundManager::BGM);
}

void MainGameScene::Update(float _dt)
{
	//// ����� �׽�Ʈ�� �ڵ�
	//int temp = 0;
	//SoundManager::GetInstance()->fsystem->getChannelsPlaying(&temp);
	//OutputDebugString(std::to_wstring(temp).c_str());
	//OutputDebugString(L"\n");


	Scene::Update(_dt);

	if (this->managers->GetKeyManager()->GetKeyState(KEY::ESC) == KEY_STATE::DOWN)
	{
		SetScenePause(!GetScenePause());
	}

	if (GetScenePause())
	{
		return;
	}

	if (this->cutsceneTime > 0.0f)
	{
		dealer->SetGameState(DEALER_STATE::ATTACK);
		this->soundDelay += _dt;
		if (!this->soundFlag && this->soundDelay >= 1.0f)
		{
			SoundManager::GetInstance()->Play(SoundManager::PLAYEREFFECT, SoundManager::DEALSKILLATCK);
			SoundManager::GetInstance()->Play(SoundManager::VOICE, SoundManager::DEALVOICE);
			this->soundFlag = true;
			soundDelay = 0.0f;
		}
		this->SetIsPause(true);
		this->cutsceneTime -= _dt;
		if (this->cutsceneTime <= 0.0f)
		{
			ActiveSkill();
			this->soundFlag = false;
		}
	}
	else
	{
		this->SetIsPause(false);
	}
	if (this->managers->GetKeyManager()->GetKeyState(KEY::LSHIFT) == KEY_STATE::DOWN &&
		this->barDealerZ->GetZ() == 0
		)
	{
		this->cutsceneTime = this->CUTSCENE_ENTERTIME + this->CUTSCENE_STAYTIME + this->CUTSCENE_EXITTIME;
		this->SetIsPause(true);
	}

	if (this->textLeftTime->GetPlayleftSecond() <= 0.0f)
	{
		this->textLeftTime->SetPlayleftSecond(0.0f);
		dealer->SetGameState(DEALER_STATE::ATTACK);
		dealer->LastAttack(true);
		this->SetIsPause(true);
		this->cutsceneTime -= _dt;
		if (this->cutsceneTime <= 0.0f)
		{
			isMainEnd = true;
			LastActiveSkill();
			isCallOnce = true;


			dealAniElapsedTime += _dt;
			if (dealAniElapsedTime >= 5.5f)
			{
				// ���� ������ �߰�
				float playTime = std::floor(textLeftTime->GetMAX_PLAYTIME() - this->textLeftTime->GetPlayleftSecond());
				newData = TextPersonData(this->totalScore, "", playTime);
				RankingScene::rankingList.push_back(newData);
				this->isGameOver = true;
				sort(RankingScene::rankingList.rbegin(), RankingScene::rankingList.rend(), Compare());
				if (RankingScene::rankingList.size() < 9 ||
					std::find(RankingScene::rankingList.begin(),
						RankingScene::rankingList.end(),
						this->newData) < RankingScene::rankingList.begin() + 9)
				{
					OutputDebugString(L"work");
					this->managers->GetSceneManager()->ChangeScene("RenewalScene");
				}
				else
				{
					this->managers->GetSceneManager()->ChangeScene("RankingScene");
				}
			}
		}
	}

	else if (this->supporter->GetHP() <= 0 || this->dealer->GetHP() <= 0 || this->guardian->GetHP() <= 0)
	{
		deadAniElapsedTime += _dt;

		if (deadAniElapsedTime >= 3.f)
		{
			deadAniElapsedTime = 0.f;
			// ���� ������ �߰�
			float playTime = std::floor(textLeftTime->GetMAX_PLAYTIME() - this->textLeftTime->GetPlayleftSecond());
			newData = TextPersonData(this->totalScore, "", playTime);
			RankingScene::rankingList.push_back(newData);
			this->isGameOver = true;
			sort(RankingScene::rankingList.rbegin(), RankingScene::rankingList.rend(), Compare());
			if (RankingScene::rankingList.size() < 9 ||
				std::find(RankingScene::rankingList.begin(),
					RankingScene::rankingList.end(),
					this->newData) < RankingScene::rankingList.begin() + 9)
			{
				this->managers->GetSceneManager()->ChangeScene("RenewalScene");
			}
			else
			{
				this->managers->GetSceneManager()->ChangeScene("RankingScene");
			}
		}

	}
}

void MainGameScene::ActiveSkill()
{
	SoundManager::GetInstance()->Play(SoundManager::SCENEEFFECT, SoundManager::SoundScore, false);

	int iceCount = 0;
	int nonIceCount = 0;

	int fireballIdx = 0;

	// ��ü ���� ����Ʈ ����ͼ� ��������� ���� �� �ְ� �ƴϸ� 100�� �����ְ� ���̱�
	std::list<Object*>& objList = GetObjectListType((int)(OBJECT_TYPE::MONSTER));
	for (auto obj : objList)
	{
		Monster* monster = dynamic_cast<Monster*>(obj);
		assert(monster != nullptr && "Worng type. expended Monster but something diffrent");
		Vector2 monsterPosition = monster->GetComponent<Transform>()->GetPosition();

		// Monster HOLD
		if (monster->GetGameState() == MONSTER_STATE::HOLD)
		{
			iceCount++;

			// ���� ����ǥ ���Ϳ� �����ϰ� ǥ��
			monster->SetScoreOn(true);
			monster->SetEachMonsterScore(MonsterHOLDScores[iceCount]);
		}
		// Monster IDLE / MOVE
		else if (monster->GetGameState() == MONSTER_STATE::IDLE || monster->GetGameState() == MONSTER_STATE::MOVE)
		{
			nonIceCount++;

			// �� ���� ����ǥ ���Ϳ� �����ϰ� ǥ��
			monster->SetScoreOn(true);
			monster->SetEachMonsterScore(MonsterXHOLDScores[nonIceCount]);
		}
		// DEAD_READY ->DEAD�� ���Ͱ� �״´�
		monster->SetGameState(MONSTER_STATE::DEAD_READY);

		/*
		// ���̾ ���� ���� �׸���
		Vector2 fireballPos = monster->GetComponent<Transform>()->GetPosition();
		fireBallPool[fireballIdx]->GetComponent<Transform>()->SetPosition(fireballPos);
		*/


		// ���� ���� ���� ���� �׸���


	}

	// 5���� ���� ������
	if (iceCount <= 5)
	{
		this->totalScore += static_cast<UINT64>(512) * 5;
	}
	// 5���� ���� ������
	else
	{
		this->totalScore += static_cast<UINT64>(512) * 5;

		UINT64 icescore = 1;
		UINT64 icebase = 1024;
		for (int i = 0; i < iceCount - 5; i++)
		{
			icescore *= 2;
		}
		icescore *= icebase;
		this->totalScore += icescore;
	}

	// ������� �����/������ �ǵ� �����̸� �ǵ� �� �� ����
	if (guardian->GetShield() == true && guardian->GetSupShield() == true)
	{
		guardian->SetSupShield(false);
		guardian->SetShield(false);
	}
	// ������� ����� �ǵ� �����̸� ����� �ǵ� ����
	else if (guardian->GetShield() == true && guardian->GetSupShield() == false)
	{
		guardian->SetShield(false);
	}
	// ������� ������ �ǵ� �����̸� ������ �ǵ� ����
	else if (guardian->GetShield() == false && guardian->GetSupShield() == true)
	{
		guardian->SetSupShield(false);
	}
	// ������� �� �� �ǵ� ���°� �ƴϸ� ü�� ���
	else if (guardian->GetShield() == false && guardian->GetSupShield() == false)
	{
		// TODO: SOUND ������� ü�� ���� �� �Ҹ�
		guardian->SetHP(guardian->GetHP() - HP_DEC);
		if (guardian->GetHP() < 0)
		{
			guardian->SetGameState(GUARDIAN_STATE::DEAD);
		}
		else
		{
			guardian->SetGameState(GUARDIAN_STATE::HIT);
		}
		SoundManager::GetInstance()->Play(SoundManager::GUARDIANEFFECT, SoundManager::GUNHIT);
	}

	this->totalScore += static_cast<UINT64>(100) * nonIceCount;
	//OutputDebugString(L"work");
	this->textScore->SetScore(totalScore);
	barDealerZ->SetZ(barDealerZ->GetMaxZ());

	this->guardian->SetTargetMonster(nullptr);

	this->managers->GetCollisionManager()->ResetCollison();
	this->textFrozenCount->SetHOLDMonsterCount(0);
	// this->managers->GetSceneManager()->DeleteTypeObjects(OBJECT_TYPE::MONSTER);
}

void MainGameScene::LastActiveSkill()
{

	if (!isCallOnce)
	{
		SoundManager::GetInstance()->Play(SoundManager::SCENEEFFECT, SoundManager::SoundScore, false);
		int iceCount = 0;
		int nonIceCount = 0;

		int fireballIdx = 0;

		// ��ü ���� ����Ʈ ����ͼ� ��������� ���� �� �ְ� �ƴϸ� 100�� �����ְ� ���̱�
		std::list<Object*>& objList = GetObjectListType((int)(OBJECT_TYPE::MONSTER));
		for (auto obj : objList)
		{
			Monster* monster = dynamic_cast<Monster*>(obj);
			assert(monster != nullptr && "Worng type. expended Monster but something diffrent");
			Vector2 monsterPosition = monster->GetComponent<Transform>()->GetPosition();

			// Monster HOLD
			if (monster->GetGameState() == MONSTER_STATE::HOLD)
			{
				iceCount++;

				// ���� ����ǥ ���Ϳ� �����ϰ� ǥ��
				monster->SetScoreOn(true);
				monster->SetEachMonsterScore(MonsterHOLDScores[iceCount]);
			}
			// Monster IDLE / MOVE
			else if (monster->GetGameState() == MONSTER_STATE::IDLE || monster->GetGameState() == MONSTER_STATE::MOVE)
			{
				nonIceCount++;

				// �� ���� ����ǥ ���Ϳ� �����ϰ� ǥ��
				monster->SetScoreOn(true);
				monster->SetEachMonsterScore(MonsterXHOLDScores[nonIceCount]);
			}
			// DEAD_READY ->DEAD�� ���Ͱ� �״´�
			monster->SetGameState(MONSTER_STATE::DEAD_READY);

			/*
			// ���̾ ���� ���� �׸���
			Vector2 fireballPos = monster->GetComponent<Transform>()->GetPosition();
			fireBallPool[fireballIdx]->GetComponent<Transform>()->SetPosition(fireballPos);
			*/


			// ���� ���� ���� ���� �׸���


		}

		// 5���� ���� ������
		if (iceCount <= 5)
		{
			this->totalScore += static_cast<UINT64>(512) * 5;
		}
		// 5���� ���� ������
		else
		{
			this->totalScore += static_cast<UINT64>(512) * 5;

			UINT64 icescore = 1;
			UINT64 icebase = 1024;
			for (int i = 0; i < iceCount - 5; i++)
			{
				icescore *= 2;
			}
			icescore *= icebase;
			this->totalScore += icescore;
		}

		// ������� �����/������ �ǵ� �����̸� �ǵ� �� �� ����
		if (guardian->GetShield() == true && guardian->GetSupShield() == true)
		{
			guardian->SetSupShield(false);
			guardian->SetShield(false);
		}
		// ������� ����� �ǵ� �����̸� ����� �ǵ� ����
		else if (guardian->GetShield() == true && guardian->GetSupShield() == false)
		{
			guardian->SetShield(false);
		}
		// ������� ������ �ǵ� �����̸� ������ �ǵ� ����
		else if (guardian->GetShield() == false && guardian->GetSupShield() == true)
		{
			guardian->SetSupShield(false);
		}
		// ������� �� �� �ǵ� ���°� �ƴϸ� ü�� ���
		else if (guardian->GetShield() == false && guardian->GetSupShield() == false)
		{
			// TODO: SOUND ������� ü�� ���� �� �Ҹ�
			guardian->SetHP(guardian->GetHP() - HP_DEC);
			if (guardian->GetHP() < 0)
			{
				guardian->SetGameState(GUARDIAN_STATE::DEAD);
			}
			else
			{
				guardian->SetGameState(GUARDIAN_STATE::HIT);
			}
			SoundManager::GetInstance()->Play(SoundManager::GUARDIANEFFECT, SoundManager::GUNHIT);
		}

		this->totalScore += static_cast<UINT64>(100) * nonIceCount;
	}
	//OutputDebugString(L"work");
	this->textScore->SetScore(totalScore);
	barDealerZ->SetZ(barDealerZ->GetMaxZ());
	this->managers->GetCollisionManager()->ResetCollison();

}

