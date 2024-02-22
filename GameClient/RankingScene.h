#pragma once
#include "ClientHeaders.h"
#include "TextPersonData.h"

class MainGameScene;

/// <summary>
/// ������
/// ��ŷ �� �۾�
/// </summary>
class RankingScene : public Scene
{
	/// �׽�Ʈ �ڵ�
	std::string uiStr;

	// for�� ��ȸ ������
	TextPersonData curData;

	// ��ŷ ���ŵǸ�
	bool hasNewRank;

	// �̸� �Է��� �ؽ�Ʈ
	wchar_t nameText[256];

	// �Է¹޾� �����ϴ� �ؽ�Ʈ
	char* nameStr;

	// ��ŷ ���� �� �Է��� ��ġ
	std::pair<int, int> namePos;

	float totalPlayTime;

	MainGameScene* mainGameScene;
	int typeCount;
	float elapsedTime;
	bool changeWhite;

public:
	RankingScene(ManagerSet* _managers);
	~RankingScene();
	void Enter() override;
	void Exit() override;
	void Update(float _dt);
	void Render(GraphicsEngine* _graphicEngine) override;
	
	// txt ���� ����� ����
	void SaveRanking();
	void LoadRanking();

	// ��ŷ ����ϴ� �Լ�
	void PrintRanking(GraphicsEngine* _graphicsEngine);
	// 3��° ���ڸ��� ,�� �߰��ϴ� �Լ�
	std::string InsertCommaToScore(UINT64 _score);

	// �Է��� ���� ������ �޽��� �Լ� �ݷ�
	void InputName(int _index);

	// ����� ��ŷ ����Ʈ
	static std::vector<TextPersonData> rankingList;
	void SetMainGameScene(MainGameScene* val) { mainGameScene = val; }
	void SetTotalPlayTime(float val) { totalPlayTime = val; }

	void ChangeTypeCount();
};

