#pragma once
#include "ClientHeaders.h"

/// <summary>
/// ������
/// ��ŷ ����!�� �ֱ� ����
/// �ϳ� �� ����
/// </summary>
class RankingRenewalScene : public Scene
{
	// ��� �ؽ�Ʈ
	std::string outputText;

	// ��� �ð�
	float outputTime;

public:
	RankingRenewalScene(ManagerSet* _managers);
	~RankingRenewalScene();

	void Enter() override;
	void Exit() override;
	void Update(float _dt);
	void Render(GraphicsEngine* _graphicsEngine) override;
};

