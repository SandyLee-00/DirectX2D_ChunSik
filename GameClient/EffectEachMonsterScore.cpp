#include "EffectEachMonsterScore.h"

EffectEachMonsterScore::EffectEachMonsterScore(ManagerSet* _managers)
	: Object("EffectEachMonsterScore", _managers, OBJECT_TYPE::ATTACHMENT, { 0, 0 })
	, isScoreOn(false)
	, elapsedTime(0.0f)
	, eachMonsterScore(0)
	, monster(nullptr)
{

}

EffectEachMonsterScore::~EffectEachMonsterScore()
{

}

void EffectEachMonsterScore::Start()
{

}

void EffectEachMonsterScore::Update(float _deltaTime)
{
	auto* transform = GetComponent<Transform>();

	// ���� ����Ʈ isScoreOn �Ǹ� ������ �ð� ������ Off �ϱ�
	if (isScoreOn == true)
	{
		elapsedTime += _deltaTime;
		if (elapsedTime >= EACH_MONSTER_SCORE_EFFECTIME)
		{
			elapsedTime = 0.0f;
			isScoreOn = false;
			eachMonsterScore = 0;
		}
	}
}

void EffectEachMonsterScore::FinalUpdate(float _deltaTime)
{

}

void EffectEachMonsterScore::Render(GraphicsEngine* _graphicsEngine)
{
	Vector2 position = GetComponent<Transform>()->GetPosition();
	const int OFFSET_X = 20;
	const int OFFSET_Y = -30;
	position = { position.x + OFFSET_X, position.y + OFFSET_Y };

	std::string scoreString = "";
	scoreString += "+ ";
	scoreString += std::to_string(this->eachMonsterScore);

	// �׸��� �� �� ����
	_graphicsEngine->ChangeFontSize(25.f);
	_graphicsEngine->ColorSet(D2D1::ColorF::White);
	
	// ���� ����Ʈ isScoreOn �Ǹ� �׸���
	if (isScoreOn == true)
	{
		_graphicsEngine->DrawString((int)position.x, (int)position.y, scoreString);
	}

	// �׸� �� �� �ǵ�����
	_graphicsEngine->ColorSet(D2D1::ColorF::Black);
	_graphicsEngine->ChangeFontSize(12.f);
}

void EffectEachMonsterScore::DebugRender(GraphicsEngine* _graphicsEngine)
{

}
