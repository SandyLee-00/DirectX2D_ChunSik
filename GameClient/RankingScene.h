#pragma once
#include "ClientHeaders.h"
#include "TextPersonData.h"

class MainGameScene;

/// <summary>
/// 김정우
/// 랭킹 씬 작업
/// </summary>
class RankingScene : public Scene
{
	/// 테스트 코드
	std::string uiStr;

	// for문 순회 데이터
	TextPersonData curData;

	// 랭킹 갱신되면
	bool hasNewRank;

	// 이름 입력할 텍스트
	wchar_t nameText[256];

	// 입력받아 저장하는 텍스트
	char* nameStr;

	// 랭킹 갱신 시 입력할 위치
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
	
	// txt 파일 입출력 관련
	void SaveRanking();
	void LoadRanking();

	// 랭킹 출력하는 함수
	void PrintRanking(GraphicsEngine* _graphicsEngine);
	// 3번째 숫자마다 ,를 추가하는 함수
	std::string InsertCommaToScore(UINT64 _score);

	// 입력을 위한 윈도우 메시지 함수 콜러
	void InputName(int _index);

	// 출력할 랭킹 리스트
	static std::vector<TextPersonData> rankingList;
	void SetMainGameScene(MainGameScene* val) { mainGameScene = val; }
	void SetTotalPlayTime(float val) { totalPlayTime = val; }

	void ChangeTypeCount();
};

