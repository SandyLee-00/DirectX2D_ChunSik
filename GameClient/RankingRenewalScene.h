#pragma once
#include "ClientHeaders.h"

/// <summary>
/// 김정우
/// 랭킹 진입!을 넣기 위해
/// 하나 더 만듬
/// </summary>
class RankingRenewalScene : public Scene
{
	// 출력 텍스트
	std::string outputText;

	// 출력 시간
	float outputTime;

public:
	RankingRenewalScene(ManagerSet* _managers);
	~RankingRenewalScene();

	void Enter() override;
	void Exit() override;
	void Update(float _dt);
	void Render(GraphicsEngine* _graphicsEngine) override;
};

