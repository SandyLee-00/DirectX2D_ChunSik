#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

class Monster;
class EffectEachMonsterScore
	: public Object
{
	// -----------------------------------
	// 밸런스 시트 const 값들
	const float EACH_MONSTER_SCORE_EFFECTIME = 2.0f;

	// 밸런스 시트 const 값들
	// -----------------------------------

private:
	bool isScoreOn;
	float elapsedTime;
	UINT64 eachMonsterScore;

	Monster* monster;

public:
	EffectEachMonsterScore(ManagerSet* _managers);
	~EffectEachMonsterScore();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetScoreOn(bool _isScoreOn) { isScoreOn = _isScoreOn; }
	void SetMonster(Monster* _monster) { monster = _monster; }
	void SetEachMonsterScore(UINT64 _eachMonsterScore) { eachMonsterScore = _eachMonsterScore; }

};
