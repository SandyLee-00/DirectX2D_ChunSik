#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"
#include "TextPersonData.h"

/// <summary>
/// 이서영
/// 서포터/가디언/딜러 / 몬스터
/// 계층구조 안만들고 전부 씬에 넣었다
/// 상속구조 만들어서 Pawn으로 관리하고 싶었다
/// 일단 구현하고 올리는게 나을 것이라고 생각해서 갈아엎었다
/// 
/// 구현하고 보니까 상대 클래스 함수 알아야 해서 dynamic_cast로 바꾼다 흠....
/// 
/// </summary>
class TextFrozenCount;
class TextLeftTime;
class TextScore;
class Monster;
class BarDealerZ;
class Dealer;
class Guardian;
class Supporter;
class RankingScene;
class EffectFireBall;
class EffectEachMonsterScore;
class WhiteEffect;

class MainGameScene
	: public Scene
{
private:
	// In Database
	UINT64 totalScore;

	// -----------------------------------
	// 밸런스 시트 const 값들
	const int ICED_SCORE1 = 512;
	const int ICED_SCORE2 = 1024;
	const int NON_ICED_SCORE = 100;
	const int BOUNSE_SCORE = 50'000;

	// 딜러 컷신 연출(등장 시간)
	const float CUTSCENE_ENTERTIME = 1.0f;
	// 딜러 컷신 연출(정지 시간)
	const float CUTSCENE_STAYTIME = 0.5f;
	// 딜러 컷신 연출(사라지는 시간)
	const float CUTSCENE_EXITTIME = 0.5f;

	// 가디언 체력 감소 수치 (서포터 쉴드)
	const int HP_DEC_SUPPORTER_SHIELD = 0;

	// 가디언 체력 감소 수치 (가디언 쉴드)
	const int HP_DEC_GUARDIAN_SHIELD = 0;

	// 가디언 체력 감소 수치
	const int HP_DEC = 2;

	// 밸런스 시트 const 값들
	// -----------------------------------

	// In Database

	float cutsceneTime;

	float deadAniElapsedTime;
	float dealAniElapsedTime;

	bool isMainEnd;
	bool isCallOnce;


	ObjectPool<Monster, 100>* monsterPool;
	/*std::vector<EffectFireBall*> fireBallPool;*/
	std::vector<UINT64> MonsterHOLDScores;
	std::vector<UINT64> MonsterXHOLDScores;

	ManagerSet* managers;
	TextFrozenCount* textFrozenCount;
	TextLeftTime* textLeftTime;
	TextScore* textScore;

	BarDealerZ* barDealerZ;

	Dealer* dealer;
	Guardian* guardian;
	Supporter* supporter;

	bool isGameOver;

	TextPersonData newData;
	RankingScene* rankingScene;

	bool soundFlag;
	
	float soundDelay;

public:
	MainGameScene(ManagerSet* _managers);
	~MainGameScene();
	void Enter() override;
	void Exit() override;

	void Update(float _dt) override;

	void ActiveSkill();
	void LastActiveSkill();

	bool GetIsGameOver() const { return isGameOver; }
	void SetIsGameOver(bool val) { isGameOver = val; }
	TextPersonData GetNewData() const { return newData; }
	TextLeftTime* GetTextLeftTime() const { return textLeftTime; }
	void SetRankingScene(RankingScene* val) { rankingScene = val; }
};

