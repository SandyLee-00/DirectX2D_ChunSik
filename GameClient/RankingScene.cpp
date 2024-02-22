#include "RankingScene.h"
#include "BackGroundObject.h"
#include "ManagerSet.h"
#include "ButtonToTitle.h"
#include "TextPersonData.h"
#include "MainGameScene.h"
#include "TextLeftTime.h"

#include <fstream>
#include <sstream>

#include "SoundManager.h"

// UI 상수들
const RECT TEXT_BOX = { 682,35,1238,161 };
const RECT RANK_RECT = { 150, 180,360,250 };
const RECT SCORE_RECT = { 360,180,815,250 };
const RECT NAME_RECT = { 815,180,1240,250 };
const RECT TIME_RECT = { 1240, 180,1450,250 };
const RECT CLEAR_RECT = { 1450 ,180,1770,250 };
const RECT TITLE_BUTTON = { 1680,960,1895,1037 };

extern HWND gHWnd;
extern HWND gHEdit;

RankingScene::RankingScene(ManagerSet* _managers)
	: Scene(_managers)
	, uiStr("test")
	, curData{}
	, hasNewRank(false)
	, nameText{}
	, nameStr(nullptr)
	, namePos({ 0,0 })
	, mainGameScene(nullptr)
	, totalPlayTime(0.f)
	, typeCount(0)
	, elapsedTime(0.f)
	, changeWhite(false)
{
	LoadRanking();
	nameStr = new char[256];
}

RankingScene::~RankingScene()
{
	delete[] nameStr;
}

void RankingScene::Enter()
{
	typeCount = 0;
	DeleteAllObjects();
	SoundManager::GetInstance()->Play(SoundManager::BGM, SoundManager::Ranking, true);

	//LoadRanking();


	// 디버깅용 빈 오브젝트
	BackGroundObject* obj = new BackGroundObject(this->managers);
	obj->SetName("RankingScene");
	managers->GetSceneManager()->AddObject(obj);

	ButtonToTitle* buttonToTitle = new ButtonToTitle(this->managers);
	buttonToTitle->GetComponent<Transform>()->SetPosition({ (int)TITLE_BUTTON.left, (int)TITLE_BUTTON.top });
	buttonToTitle->SetName("ButtonToTitle");
	buttonToTitle->SetSize(Vector2((int)(TITLE_BUTTON.right - TITLE_BUTTON.left), (int)TITLE_BUTTON.bottom - (int)TITLE_BUTTON.top));
	//buttonToTitle->SetTextAll("타이틀로 이동", Vector2((int)TITLE_BUTTON.left, (int)TITLE_BUTTON.top), 20.f);
	managers->GetSceneManager()->AddObject(buttonToTitle);

	if (this->mainGameScene->GetIsGameOver())
	{
		// 갱신이 되는 조건이면
		if (this->rankingList.size() < 10 ||
			std::find(this->rankingList.begin(), this->rankingList.end(), this->mainGameScene->GetNewData())
			< this->rankingList.begin() + 9)
		{
			this->hasNewRank = true;
			int index = std::find(this->rankingList.begin(), this->rankingList.end(),
				this->mainGameScene->GetNewData()) - this->rankingList.begin();
			InputName(index);
		}

		else
		{
			this->hasNewRank = false;
		}
	}
}

void RankingScene::Exit()
{

	if (this->mainGameScene->GetIsGameOver())
	{
		for (auto it = this->rankingList.begin(); it != this->rankingList.end(); it++)
		{
			/*if (it->GetTotalSec() == this->mainGameScene->GetNewData().GetTotalSec())
			{
				if (it->GetScore() == this->mainGameScene->GetNewData().GetScore())
				{
					it->SetName(nameStr);
				}
			}*/

			if (it == std::find(this->rankingList.begin(), this->rankingList.end(), this->mainGameScene->GetNewData()))
			{
				it->SetName(nameStr);
			}
		}
	}
	SaveRanking();
	SetFocus(gHWnd);
	DestroyWindow(gHEdit);
	this->mainGameScene->SetIsGameOver(false);

	SoundManager::GetInstance()->Stop(SoundManager::BGM);
	//DeleteAllObjects();
}

void RankingScene::Update(float _dt)
{
	Scene::Update(_dt);

	GetWindowTextW(gHEdit, this->nameText, 9);
	//if (!changeWhite)
	{
		elapsedTime += _dt;
		if (elapsedTime >= 0.5f)
		{
			elapsedTime = 0.f;
			changeWhite = true;
		}
	}

	//ChangeTypeCount();
}

void RankingScene::Render(GraphicsEngine* _graphicEngine)
{

	Scene::Render(_graphicEngine);
	_graphicEngine->ColorSet(D2D1::ColorF::Black);

	/// 임시 더미 출력 --------------
	/// TODO
	/// 텍스트 크기 조절
	/// 중앙 출력
	/// 
	// 명예의 전당 타이틀
	//_graphicEngine->DrawEmptyRect((int)TEXT_BOX.left, TEXT_BOX.top, TEXT_BOX.right, TEXT_BOX.bottom);
	//this->uiStr = "명예의 전당";
	//_graphicEngine->DrawString((TEXT_BOX.left + TEXT_BOX.right) / 2, (TEXT_BOX.top + TEXT_BOX.bottom) / 2, this->testStr);

	//_graphicEngine->ChangeFontSize(70.f);
	//_graphicEngine->DrawString(TEXT_BOX.left + 130, TEXT_BOX.top + 25, this->uiStr);
	_graphicEngine->ChangeFontSize(46.f);

	// 순위
	//_graphicEngine->DrawEmptyRect((int)RANK_RECT.left, RANK_RECT.top, RANK_RECT.right, RANK_RECT.bottom);
	this->uiStr = "순위";
	_graphicEngine->DrawString(RANK_RECT.left + 62, RANK_RECT.top + 6, this->uiStr);

	// 점수
	//_graphicEngine->DrawEmptyRect((int)SCORE_RECT.left, SCORE_RECT.top, SCORE_RECT.right, (int)SCORE_RECT.bottom);
	this->uiStr = "점수";
	_graphicEngine->DrawString(SCORE_RECT.left + 107, SCORE_RECT.top + 6, this->uiStr);

	// 중간 출력 함수 만들긴 했는데 하드코딩이 맘 편하다
	//_graphicEngine->CenterDrawString(SCORE_RECT.left, SCORE_RECT.top, this->testStr);

	// 이름
	//_graphicEngine->DrawEmptyRect((int)NAME_RECT.left, (int)NAME_RECT.top, (int)NAME_RECT.right, (int)NAME_RECT.bottom);
	this->uiStr = "이름";
	_graphicEngine->DrawString(NAME_RECT.left + 92, NAME_RECT.top + 6, this->uiStr);

	// 시간
	//_graphicEngine->DrawEmptyRect((int)TIME_RECT.left, (int)TIME_RECT.top, (int)TIME_RECT.right, (int)TIME_RECT.bottom);
	this->uiStr = "시간";
	_graphicEngine->DrawString(TIME_RECT.left + 5, TIME_RECT.top + 6, this->uiStr);

	// 클리어 여부
	//_graphicEngine->DrawEmptyRect((int)CLEAR_RECT.left, (int)CLEAR_RECT.top, (int)CLEAR_RECT.right, (int)CLEAR_RECT.bottom);
	this->uiStr = "클리어 여부";
	_graphicEngine->DrawString(CLEAR_RECT.left + 28, CLEAR_RECT.top + 6, this->uiStr);

	// 순위
	for (int i = 0; i < 10; i++)
	{
		// 순위는 i + 1
		/*_graphicEngine->DrawEmptyRect(150, (int)RANK_RECT.bottom + i * 70, 1770,
			(int)RANK_RECT.bottom + (i + 1) * 70);*/
		switch (i + 1)
		{
		case 1:
			_graphicEngine->DrawString(212, (int)RANK_RECT.bottom + i * 70 + 20,
				std::to_string(i + 1) + "st");
			break;
		case 2:
			_graphicEngine->DrawString(212, (int)RANK_RECT.bottom + i * 70 + 20,
				std::to_string(i + 1) + "nd");
			break;
		case 3:
			_graphicEngine->DrawString(212, (int)RANK_RECT.bottom + i * 70 + 20,
				std::to_string(i + 1) + "rd");
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			_graphicEngine->DrawString(212, (int)RANK_RECT.bottom + i * 70 + 20,
				std::to_string(i + 1) + "th");
			break;
		default:
			break;
		}
	}
	/// 임시 더미 출력 --------------


	PrintRanking(_graphicEngine);

	if (this->mainGameScene->GetIsGameOver())
	{

		if (this->hasNewRank)
		{
			int tempSize = WideCharToMultiByte(CP_ACP, 0, this->nameText, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, this->nameText, -1, nameStr, tempSize, nullptr, nullptr);
			for (int i = 0; i < tempSize; i++)
			{
				if (nameStr[i] >= 97)
				{
					nameStr[i] -= 32;
				}
			}
			/*if (typeCount >= 0 && typeCount <= 8)
			{
			}*/
			if (changeWhite)
			{
				changeWhite = false;
				_graphicEngine->ColorSet(D2D1::ColorF::White);
				_graphicEngine->DrawRectangle(this->namePos.first, this->namePos.second + 135, this->namePos.first + 28 * 13 + 5, this->namePos.second + 140);
			}
			else
			{
				_graphicEngine->DrawRectangle(this->namePos.first, this->namePos.second + 135, this->namePos.first + 28 * 13 + 5, this->namePos.second + 140);
			}

			_graphicEngine->ColorSet(D2D1::ColorF::Green);
			_graphicEngine->DrawTextCC(this->namePos.first, this->namePos.second + 90, nameStr);
			_graphicEngine->ColorSet(D2D1::ColorF::Black);


		}

		// 갱신 실패
		if (!this->hasNewRank)
		{
			UINT64 score = this->mainGameScene->GetNewData().GetScore();
			std::string scoreText = InsertCommaToScore(score);
			_graphicEngine->DrawString((int)SCORE_RECT.left, 20 + (int)SCORE_RECT.bottom + 630, scoreText);

			_graphicEngine->DrawString((int)NAME_RECT.left, 20 + (int)NAME_RECT.bottom + 630,
				"--------");

			float totalTime = this->mainGameScene->GetNewData().GetTotalSec();
			float totalMin = totalTime / 60;
			float totalSec = totalTime - std::floor(totalMin) * 60;
			std::string timeText = std::to_string((int)std::floor(totalMin)) + "'" +
				std::to_string((int)std::round(totalSec));
			_graphicEngine->DrawString((int)TIME_RECT.left, 20 + (int)TIME_RECT.bottom +
				630, timeText);

			if (totalTime >= totalPlayTime)
			{
				_graphicEngine->DrawString((int)CLEAR_RECT.left,
					20 + (int)CLEAR_RECT.bottom + 630, "     CLEAR");
			}
			if (totalTime < totalPlayTime)
			{
				_graphicEngine->DrawString((int)CLEAR_RECT.left,
					20 + (int)CLEAR_RECT.bottom + 630, "GAME OVER");
			}
		}
	}

	_graphicEngine->ChangeFontSize(12.f);

}

void RankingScene::SaveRanking()
{
	// 파일 명
	std::string fileName = "Ranking.txt";

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		std::cerr << "Failed to open" << std::endl;
	}
	else
	{
		if (this->rankingList.empty())
		{
			std::cerr << "데이터가 담기지 않았습니다." << std::endl;
			return;
		}


		for (auto iter = rankingList.begin(); iter != rankingList.end(); iter++)
		{
			// 점수
			ofs << iter->GetScore() << ",";

			// 이름
			ofs << iter->GetName() << ",";

			// 시간
			ofs << iter->GetTotalSec();

			ofs << std::endl;
		}

		ofs.close();
	}


}

void RankingScene::LoadRanking()
{
	static int callCount = 0;

	if (callCount > 0)
	{
		return;
	}

	// 파일 명
	std::string fileName = "Ranking.txt";

	// 파일을 불러서 리스트에 저장하는 부분

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cerr << "Can't find file" << std::endl;
	}
	else
	{
		std::string line;

		for (int i = 0; i < 9; i++)
		{
			while (std::getline(ifs, line))
			{
				if (line == "")
				{
					continue;
				}

				TextPersonData tempData{};
				std::istringstream iss(line);

				std::string score;
				std::getline(iss, score, ',');
				UINT64 llScore = std::stoull(score);
				tempData.SetScore(llScore);

				std::string name;
				std::getline(iss, name, ',');
				tempData.SetName(name);

				std::string totalSec;
				std::getline(iss, totalSec, ',');
				tempData.SetTotalSec(std::stof(totalSec));

				this->rankingList.push_back(tempData);
			}
		}

		ifs.close();
	}

	callCount++;
}

void RankingScene::PrintRanking(GraphicsEngine* _graphicsEngine)
{
	// 아직 랭킹 시트가 쌓이지 않았을떄
	if (this->rankingList.size() < 9)
	{
		for (size_t i = 0; i < this->rankingList.size(); i++)
			//for (auto iter = this->rankingList.begin(); iter != this->rankingList.end(); iter++)
		{
			_graphicsEngine->ColorSet(D2D1::ColorF::Black);

			curData = this->rankingList[i];
			if (this->mainGameScene->GetIsGameOver() && curData == *std::find(this->rankingList.begin(), this->rankingList.end(), this->mainGameScene->GetNewData()))
			{
				_graphicsEngine->ColorSet(D2D1::ColorF::Green);
			}

			// TODO 점수 -> BigInt로 바꾸고 숫자가 제대로 안 나오고 있음
			UINT64 score = curData.GetScore();
			std::string scoreText = InsertCommaToScore(score);

			_graphicsEngine->DrawString((int)SCORE_RECT.left, 20 + (int)SCORE_RECT.bottom +
				i * 70, scoreText);

			// 이름
			std::string name = curData.GetName();
			// 모든 글자는 대문자로
			std::transform(name.begin(), name.end(), name.begin(),
				[](unsigned char c) {return std::toupper(c); });
			_graphicsEngine->DrawString((int)NAME_RECT.left, 20 + (int)NAME_RECT.bottom +
				i * 70, name);

			// 시간
			float totalTime = curData.GetTotalSec();
			float totalMin = totalTime / 60;
			float totalSec = totalTime - std::floor(totalMin) * 60;
			std::string timeText = std::to_string((int)std::floor(totalMin)) + "'" +
				std::to_string((int)std::round(totalSec));

			/// TODO 초는 1의 자리수여도 00 이렇게 출력
			_graphicsEngine->DrawString((int)TIME_RECT.left, 20 + (int)TIME_RECT.bottom +
				i * 70, timeText);

			// 클리어 여부
			// 300초가 되면 클리어
			if (totalTime >= totalPlayTime)
			{
				_graphicsEngine->DrawString((int)CLEAR_RECT.left,
					20 + (int)CLEAR_RECT.bottom + i * 70, "     CLEAR");
			}
			if (totalTime < totalPlayTime)
			{
				_graphicsEngine->DrawString((int)CLEAR_RECT.left,
					20 + (int)CLEAR_RECT.bottom + i * 70, "GAME OVER");
			}
		}

		for (size_t i = this->rankingList.size(); i < 9; i++)
		{
			_graphicsEngine->ColorSet(D2D1::ColorF::Black);

			_graphicsEngine->DrawString((int)SCORE_RECT.left, 20 + (int)SCORE_RECT.bottom +
				i * 70, "----------");
			_graphicsEngine->DrawString((int)NAME_RECT.left, 20 + (int)NAME_RECT.bottom + i * 70,
				"----------");
			_graphicsEngine->DrawString((int)TIME_RECT.left, 20 + (int)TIME_RECT.bottom + i * 70,
				"----");
			_graphicsEngine->DrawString((int)CLEAR_RECT.left, 20 + (int)CLEAR_RECT.bottom +
				i * 70, " --------");
		}
	}
	// 랭킹이 쌓이면

	/// 현재 그냥 10개 넘으면 삭제할려고 했는데
	/// 이제 새로운 데이터를 랭킹 리스트의 마지막과 비교해서
	/// 마지막인가 아닌가를 비교해 
	/// 갱신인가 아닌가를 판단하자
	if (this->rankingList.size() >= 9)
	{
		if (this->rankingList.size() > 9)
		{
			// 9개 유지
			rankingList.erase(rankingList.begin() + 9, rankingList.end());
		}

		for (size_t i = 0; i < this->rankingList.size(); i++)
		{
			_graphicsEngine->ColorSet(D2D1::ColorF::Black);
			curData = this->rankingList[i];

			if (std::find(this->rankingList.begin(), this->rankingList.end(), this->mainGameScene->GetNewData()) != this->rankingList.end())
			{
				if (this->mainGameScene->GetIsGameOver() && curData == *std::find(this->rankingList.begin(), this->rankingList.end(), this->mainGameScene->GetNewData()))
				{
					_graphicsEngine->ColorSet(D2D1::ColorF::Green);
				}
			}

			// 점수
			UINT64 score = curData.GetScore();
			std::string scoreText = InsertCommaToScore(score);

			_graphicsEngine->DrawString((int)SCORE_RECT.left, 20 + (int)SCORE_RECT.bottom +
				i * 70, scoreText);

			// 이름
			std::string name = curData.GetName();
			// 모든 글자는 대문자로
			std::transform(name.begin(), name.end(), name.begin(),
				[](unsigned char c) {return std::toupper(c); });
			_graphicsEngine->DrawString((int)NAME_RECT.left, 20 + (int)NAME_RECT.bottom + i * 70,
				name);

			// 시간
			float totalTime = curData.GetTotalSec();
			float totalMin = totalTime / 60;
			float totalSec = totalTime - std::floor(totalMin) * 60;
			std::string timeText = std::to_string((int)std::floor(totalMin)) + "'" +
				std::to_string((int)std::round(totalSec));
			_graphicsEngine->DrawString((int)TIME_RECT.left, 20 + (int)TIME_RECT.bottom + i * 70,
				timeText);

			// 클리어 여부
			// 300초가 되면 클리어
			if (totalTime >= totalPlayTime)
			{
				_graphicsEngine->DrawString((int)CLEAR_RECT.left,
					20 + (int)CLEAR_RECT.bottom + i * 70, "     CLEAR");
			}
			if (totalTime < totalPlayTime)
			{
				_graphicsEngine->DrawString((int)CLEAR_RECT.left,
					20 + (int)CLEAR_RECT.bottom + i * 70, "GAME OVER");
			}
		}
	}
}

std::string RankingScene::InsertCommaToScore(UINT64 _score)
{
	// 문자열을 조작할 스트림 
	std::ostringstream oss;
	oss << _score;

	std::string numStr = oss.str();
	std::string result;

	int len = numStr.length();
	int commaCount = (len - 1) / 3;

	for (int i = 0; i < len; i++)
	{
		result += numStr[i];
		if (i < len - 1 && (len - 1 - i) % 3 == 0 && commaCount>0)
		{
			result += ",";
			commaCount--;
		}
	}

	return result;
}

void RankingScene::InputName(int _index)
{
	this->namePos = { 815,180 + 70 * _index };
	DestroyWindow(gHEdit);
	gHEdit = CreateWindowW(L"edit", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		750, 180 + 70 * _index, 25, 100, gHWnd, (HMENU)100, NULL, NULL);
	SendMessage(gHEdit, EM_LIMITTEXT, (WPARAM)8, 0);
	gHEdit = GetWindow(gHWnd, GW_CHILD);
	SetFocus(gHEdit);
	//CreateCaret(gHEdit, NULL, 2, 20);
	ShowWindow(gHWnd, SW_SHOW);
	UpdateWindow(gHWnd);
	//ShowCaret(gHEdit);
}

void RankingScene::ChangeTypeCount()
{
	if (this->managers->GetKeyManager()->GetKeyState(KEY::Q) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::W) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::E) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::R) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::T) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::Y) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::U) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::I) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::O) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::P) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::A) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::S) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::D) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::F) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::G) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::H) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::J) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::K) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::L) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::Z) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::X) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::C) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::V) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::B) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::M) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_1) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_2) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_3) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_4) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_5) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_6) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_7) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_8) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_9) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::N_0) == KEY_STATE::DOWN ||
		this->managers->GetKeyManager()->GetKeyState(KEY::SPACE) == KEY_STATE::DOWN)
	{
		if (typeCount < 8)
		{
			typeCount++;
		}
	}

	if (this->managers->GetKeyManager()->GetKeyState(KEY::BACKSPACE) == KEY_STATE::DOWN)
	{
		if (typeCount > 0)
		{
			typeCount--;
		}
	}

}

std::vector<TextPersonData> RankingScene::rankingList{};
