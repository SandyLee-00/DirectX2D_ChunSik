#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"
#include "TextPersonData.h"

/// <summary>
/// �̼���
/// ������/�����/���� / ����
/// �������� �ȸ���� ���� ���� �־���
/// ��ӱ��� ���� Pawn���� �����ϰ� �;���
/// �ϴ� �����ϰ� �ø��°� ���� ���̶�� �����ؼ� ���ƾ�����
/// 
/// �����ϰ� ���ϱ� ��� Ŭ���� �Լ� �˾ƾ� �ؼ� dynamic_cast�� �ٲ۴� ��....
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
	// �뷱�� ��Ʈ const ����
	const int ICED_SCORE1 = 512;
	const int ICED_SCORE2 = 1024;
	const int NON_ICED_SCORE = 100;
	const int BOUNSE_SCORE = 50'000;

	// ���� �ƽ� ����(���� �ð�)
	const float CUTSCENE_ENTERTIME = 1.0f;
	// ���� �ƽ� ����(���� �ð�)
	const float CUTSCENE_STAYTIME = 0.5f;
	// ���� �ƽ� ����(������� �ð�)
	const float CUTSCENE_EXITTIME = 0.5f;

	// ����� ü�� ���� ��ġ (������ ����)
	const int HP_DEC_SUPPORTER_SHIELD = 0;

	// ����� ü�� ���� ��ġ (����� ����)
	const int HP_DEC_GUARDIAN_SHIELD = 0;

	// ����� ü�� ���� ��ġ
	const int HP_DEC = 2;

	// �뷱�� ��Ʈ const ����
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

