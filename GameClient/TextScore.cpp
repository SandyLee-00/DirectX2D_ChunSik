#include "TextScore.h"
#include "RankingScene.h"
#include <sstream>

std::string InsertCommaToScore(UINT64 _score)
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

TextScore::TextScore(ManagerSet* _managers)
	: Object("TextScore", _managers, OBJECT_TYPE::UI, { 0, 0 })
	, isWorking{}
	, score(0)
{

}

TextScore::~TextScore()
{

}

void TextScore::Start()
{
	score = 0;
}

void TextScore::Update(float _deltaTime)
{
	if (isWorking == false)
	{
		return;
	}
}

void TextScore::Render(GraphicsEngine* _graphicsEngine)
{
	_graphicsEngine->DrawSprite("scoreBox", 67, 1196, 10, 700, 95);
	std::string tempScore = InsertCommaToScore(this->score);
	std::string scoreString = "Score : " + tempScore;
	_graphicsEngine->ChangeFontSize(46.f);
	_graphicsEngine->ColorSet(D2D1::ColorF::White);
	_graphicsEngine->DrawString(1246, 30, scoreString);
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(12.f);
}
