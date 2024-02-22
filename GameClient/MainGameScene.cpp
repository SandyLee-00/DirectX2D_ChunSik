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

// 랭킹씬 데이터 넘기기 위해 추가함
#include "RankingScene.h"

#include "SoundManager.h"

/// <summary>
/// 스코어를 비교하기 위해 만든 functor
/// </summary>
struct Compare
{
	bool operator()(const TextPersonData& _one, const TextPersonData& _two)
	{
		if (_one.GetScore() == _two.GetScore())
		{
			// 점수와 걸린 시간 모두 같을 때
			if (_one.GetTotalSec() == _two.GetTotalSec())
			{
				// 먼저 게임을 한 사람이 윗 순위로
				// 다음 게임하는 사람이 밑에서 올라오기 때문에
				// 여기서는 바꿔주지 않고 그냥 나가자

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
	// TODO: delete 하니까 터진다..
	delete monsterPool;
}

void MainGameScene::Enter()
{
	DeleteAllObjects();
	totalScore = 0;
	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Main, true);

	// 디버깅용 빈 오브젝트
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("MainGameScene");
	managers->GetSceneManager()->AddObject(obj);

	// __________________________________________________________
	//monsterPool = new ObjectPool<Monster, 100>(this->managers);



	// __________________________________________________________
	// 오브젝트
	dealer = new Dealer(this->managers);
	managers->GetSceneManager()->AddObject(dealer);

	guardian = new Guardian(this->managers);
	managers->GetSceneManager()->AddObject(guardian);

	supporter = new Supporter(this->managers);
	managers->GetSceneManager()->AddObject(supporter);

	guardian->SetTargetSupporter(supporter);


	// __________________________________________________________
	// Attach 하는 오브젝트

	// __________________________________________________________
	// ATTACHMENT 중 effect로 처리할 것들 
	// 가디언 공격범위
	RangeGuardianAttack* guardianAttackRange = new RangeGuardianAttack(this->managers);
	guardianAttackRange->SetParent(guardian);
	guardian->SetChild(guardianAttackRange);
	managers->GetSceneManager()->AddObject(guardianAttackRange);

	// 서포터 실드범위 
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
	// 딜러가 몬스터 없앨 때 모든 몬스터 위에 이펙트 떨어지고 DEAD_DELAYTIME 이후에 DEAD 된다
	// 풀에 파이어볼 100개 만들기
	for (int i = 0; i < 100; i++)
	{
		EffectFireBall* effectFireBall = new EffectFireBall(this->managers);
		fireBallPool.push_back(effectFireBall);
		managers->GetSceneManager()->AddObject(effectFireBall);
	}
	*/

	// 딜러가 몬스터 없앨 때 몬스터 위에 뜨는 각자 몬스터의 점수
	long long tempScore = 512;

	// 1. 얼린 몬스터 점수 표 초기화하기
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

	// 2. 안 얼린 몬스터 점수 표 초기화하기
	for (int i = 0; i < 100; i++)
	{
		MonsterXHOLDScores.push_back(100);
	}


	// __________________________________________________________
	// UI

	// 비어있는 위에 그려야 하는 것들 - 양 옆 숲 / HP 왼쪽 얼굴들 / HP 밑 회색박스 
	// 스코어 박스, 시간 박스, 얼린 적 수 박스

	BackGroundOver* backGroundOver = new BackGroundOver(this->managers);
	/*backGroundOver->SetGuardian(guardian);*/
	managers->GetSceneManager()->AddObject(backGroundOver);

	// __________________________________________________________
	// UI 

	// 딜러 Z 
	barDealerZ = new BarDealerZ(this->managers);
	barDealerZ->SetParent(dealer);
	dealer->SetChild(barDealerZ);
	managers->GetSceneManager()->AddObject(barDealerZ);
	barDealerZ->SetZ(barDealerZ->GetMaxZ());

	// 딜러 체력 부모의 HP 갖고와서 보여주기만 한다 
	BarHP* barHPDealer = new BarHP(this->managers);
	barHPDealer->SetParent(dealer);
	barHPDealer->SetMaxHP(HP_DEALER_MAX);
	managers->GetSceneManager()->AddObject(barHPDealer);

	// 서포터 체력
	BarHP* barHPSupporter = new BarHP(this->managers);
	barHPSupporter->SetParent(supporter);
	barHPDealer->SetMaxHP(HP_SUPPORTER_MAX);
	managers->GetSceneManager()->AddObject(barHPSupporter);

	// 가디언 체력
	BarHP* barHPGuardian = new BarHP(this->managers);
	barHPGuardian->SetParent(guardian);
	barHPDealer->SetMaxHP(HP_GUARDIAN_MAX);
	managers->GetSceneManager()->AddObject(barHPGuardian);

	// 현재 얼린 적
	textFrozenCount = new TextFrozenCount(this->managers);
	managers->GetSceneManager()->AddObject(textFrozenCount);

	// 남은 시간
	textLeftTime = new TextLeftTime(this->managers);
	managers->GetSceneManager()->AddObject(textLeftTime);

	// 점수
	textScore = new TextScore(this->managers);
	managers->GetSceneManager()->AddObject(textScore);

	// __________________________________________________________
	// 몬스터 스포너
	MonsterSpawner* monsterSpawner = new MonsterSpawner(this->managers);
	monsterSpawner->SetName("monsterSpawner");
	monsterSpawner->SetMonsterPool(monsterPool);
	monsterSpawner->SetDZ(barDealerZ);
	monsterSpawner->SetTF(textFrozenCount);
	managers->GetSceneManager()->AddObject(monsterSpawner);

	// __________________________________________________________
	// Collision 세팅
	// 서포터 - 몬스터 얼리기
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::SUPPORTER, OBJECT_TYPE::MONSTER);
	// 몬스터가 딜러 때리기
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::DEALER, OBJECT_TYPE::MONSTER);
	// 몬스터 - 몬스터 얼음 땡
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::MONSTER, OBJECT_TYPE::MONSTER);
	// 가디언 공격 범위 - 몬스터 가디언 범위가 인식하고 몬스터 때리기
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::MONSTER, OBJECT_TYPE::ATTACHMENT);
	// 서포터 실드 범위 - 딜러
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::DEALER, OBJECT_TYPE::ATTACHMENT);
	// 서포터 실드 범위 - 가디언
	managers->GetCollisionManager()->MarkCollisionType(OBJECT_TYPE::ATTACHMENT, OBJECT_TYPE::GUARDIAN);

	// 게임을 했는지
	this->isGameOver = false;
	// 전체 게임 시간 전달
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
	//// 디버그 테스트용 코드
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
				// 게임 데이터 추가
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
			// 게임 데이터 추가
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

	// 전체 몬스터 리스트 갖고와서 얼어있으면 점수 더 주고 아니면 100점 더해주고 죽이기
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

			// 얼은 점수표 몬스터에 전달하고 표시
			monster->SetScoreOn(true);
			monster->SetEachMonsterScore(MonsterHOLDScores[iceCount]);
		}
		// Monster IDLE / MOVE
		else if (monster->GetGameState() == MONSTER_STATE::IDLE || monster->GetGameState() == MONSTER_STATE::MOVE)
		{
			nonIceCount++;

			// 안 얼은 점수표 몬스터에 전달하고 표시
			monster->SetScoreOn(true);
			monster->SetEachMonsterScore(MonsterXHOLDScores[nonIceCount]);
		}
		// DEAD_READY ->DEAD로 몬스터가 죽는다
		monster->SetGameState(MONSTER_STATE::DEAD_READY);

		/*
		// 파이어볼 몬스터 위에 그리기
		Vector2 fireballPos = monster->GetComponent<Transform>()->GetPosition();
		fireBallPool[fireballIdx]->GetComponent<Transform>()->SetPosition(fireballPos);
		*/


		// 몬스터 점수 몬스터 위에 그리기


	}

	// 5마리 보다 적으면
	if (iceCount <= 5)
	{
		this->totalScore += static_cast<UINT64>(512) * 5;
	}
	// 5마리 보다 많으면
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

	// 가디언이 가디언/서포터 실드 상태이면 실드 둘 다 깨기
	if (guardian->GetShield() == true && guardian->GetSupShield() == true)
	{
		guardian->SetSupShield(false);
		guardian->SetShield(false);
	}
	// 가디언이 가디언 실드 상태이면 가디언 실드 깨기
	else if (guardian->GetShield() == true && guardian->GetSupShield() == false)
	{
		guardian->SetShield(false);
	}
	// 가디언이 서포터 실드 상태이면 서포터 실드 깨기
	else if (guardian->GetShield() == false && guardian->GetSupShield() == true)
	{
		guardian->SetSupShield(false);
	}
	// 가디언이 둘 다 실드 상태가 아니면 체력 깎기
	else if (guardian->GetShield() == false && guardian->GetSupShield() == false)
	{
		// TODO: SOUND 가디언이 체력 깎일 때 소리
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

		// 전체 몬스터 리스트 갖고와서 얼어있으면 점수 더 주고 아니면 100점 더해주고 죽이기
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

				// 얼은 점수표 몬스터에 전달하고 표시
				monster->SetScoreOn(true);
				monster->SetEachMonsterScore(MonsterHOLDScores[iceCount]);
			}
			// Monster IDLE / MOVE
			else if (monster->GetGameState() == MONSTER_STATE::IDLE || monster->GetGameState() == MONSTER_STATE::MOVE)
			{
				nonIceCount++;

				// 안 얼은 점수표 몬스터에 전달하고 표시
				monster->SetScoreOn(true);
				monster->SetEachMonsterScore(MonsterXHOLDScores[nonIceCount]);
			}
			// DEAD_READY ->DEAD로 몬스터가 죽는다
			monster->SetGameState(MONSTER_STATE::DEAD_READY);

			/*
			// 파이어볼 몬스터 위에 그리기
			Vector2 fireballPos = monster->GetComponent<Transform>()->GetPosition();
			fireBallPool[fireballIdx]->GetComponent<Transform>()->SetPosition(fireballPos);
			*/


			// 몬스터 점수 몬스터 위에 그리기


		}

		// 5마리 보다 적으면
		if (iceCount <= 5)
		{
			this->totalScore += static_cast<UINT64>(512) * 5;
		}
		// 5마리 보다 많으면
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

		// 가디언이 가디언/서포터 실드 상태이면 실드 둘 다 깨기
		if (guardian->GetShield() == true && guardian->GetSupShield() == true)
		{
			guardian->SetSupShield(false);
			guardian->SetShield(false);
		}
		// 가디언이 가디언 실드 상태이면 가디언 실드 깨기
		else if (guardian->GetShield() == true && guardian->GetSupShield() == false)
		{
			guardian->SetShield(false);
		}
		// 가디언이 서포터 실드 상태이면 서포터 실드 깨기
		else if (guardian->GetShield() == false && guardian->GetSupShield() == true)
		{
			guardian->SetSupShield(false);
		}
		// 가디언이 둘 다 실드 상태가 아니면 체력 깎기
		else if (guardian->GetShield() == false && guardian->GetSupShield() == false)
		{
			// TODO: SOUND 가디언이 체력 깎일 때 소리
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

