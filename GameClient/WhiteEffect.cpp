#include "WhiteEffect.h"
#include "Dealer.h"
#include "SoundManager.h"

WhiteEffect::WhiteEffect(ManagerSet* _managers)
	: Object("WhiteEffect", _managers, OBJECT_TYPE::WHITEEFFECT, { 0,0 })
	, op(0.f)
	, isOnEff(false)
	, dealer(nullptr)
	, dealCutSceneX(-1200)
	, holeTime(0.0f)
	, holeop(0.0f)
	, cutscenenum(82)
	, effEnd(false)
	, time(0.f)
	, soundFlag(false)
{

}

WhiteEffect::~WhiteEffect()
{

}

void WhiteEffect::Start()
{
	op = 1.f;
	holeop = 0.f;

	CreateComponent<Animation>();
	animation = GetComponent<Animation>();
	animation->SetOffset(Vector2{ 0,0 });

	animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", 0, 0);
}

void WhiteEffect::Update(float _deltaTime)
{
	//하고 있다면
	if (dealer->GetGameState() == DEALER_STATE::ATTACK)
	{
		time += _deltaTime;
		holeTime += _deltaTime;
		if (time > 0.7f)
		{
			dealCutSceneX = -1200;

		}
		if (dealCutSceneX >= 400)
		{
			if (op <= 0) return;

			op -= 0.03f;

		}
		else
		{
			dealCutSceneX += 100;
		}

		if (holeTime >= 4.5f)
		{
			//cutscenenum = 28;
			effEnd = true;
		}
		else if (holeTime >= 4.0f)
		{
			cutscenenum = 86;

		}
		else if (holeTime >= 3.5f)
		{
			cutscenenum = 85;
		}

		else if (holeTime >= 3.0f)
		{
			cutscenenum = 84;
		}
		else if (holeTime >= 2.6f)
		{
			holeop -= 0.05f;
		}
		else if (holeTime >= 2.5f)
		{
			cutscenenum = 83;
		}
		else if (holeTime >= 2.4f)
		{
			holeop += 0.05f;
		}
		else if (holeTime >= 2.0f)
		{
			cutscenenum = 82;
			//SoundManager::GetInstance()->Play(SoundManager::DEALEREFFECT, SoundManager::DEALSKILLATCK);
		}

		//if (holeTime >= 0.8f)
		//{
		//}

		//if (holeTime >= 0.8f)
		//{
		//	holeop -= 0.01f;
		//}
		//else if (holeTime >= 0.5f)
		//{
		//	holeop += 0.01f;
		//}

	}
	else
	{
		time = 0;
		holeTime = 0;
		//OutputDebugString(L"work\n");
		dealCutSceneX = -1200;
		isOnEff = false;
		op = 1.f;
		holeop = 0.f;
		cutscenenum = 82;
		effEnd = false;
		//cutscenenum = 28;
	}
}

void WhiteEffect::FinalUpdate(float _deltaTime)
{

}

void WhiteEffect::Render(GraphicsEngine* _graphicsEngine)
{
	//딜러 공격시 에만 그릴것
	//animation->SetSpriteRes(82, L"Animation\\dealSkillEft.txt", "deal", 0, 0);
	if (0.0f < holeTime && holeTime <= 4.5f)
	{
		this->soundFlag = false;
		// SoundManager::GetInstance()->Play(SoundManager::DEALEREFFECT, SoundManager::DEALATTACK);
		_graphicsEngine->SetIsEffOn();
		_graphicsEngine->SetEffect("de", op, 56, dealCutSceneX, 300);
		_graphicsEngine->SetEffect("bg", holeop, 76, 0, 0);
		animation->SetSpriteRes(cutscenenum, L"Animation\\dealSkillEft.txt", "deal", 0, 0);
		// _graphicsEngine->DrawSprite("dealcut", 56, (float)dealCutSceneX, 300.f, 1100, 385);
		//if (dealCutSceneX >= 500)
		//{
		//	OutputDebugString(L"호출");
		//	
		//}
		//else
		//{
		//	_graphicsEngine->SetEffect(op, 56, dealCutSceneX, 300.f);
		//}
		std::wstring str = std::to_wstring(holeTime);
		str += L"\n";
		OutputDebugString(str.c_str());
	}
	if (effEnd)
	{
		// _graphicsEngine->SetIsEffOff();
		if (!this->soundFlag)
		{
			SoundManager::GetInstance()->Play(SoundManager::MONSTEREFFECT, SoundManager::DEADMON);
			this->soundFlag = true;
		}
		_graphicsEngine->SetIsEffOff();
		animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", 0, 0);
	}
	//animation->SetSpriteRes(28, L"Animation\\nullptr.txt", "nullptr", 0, 0);


}

void WhiteEffect::DebugRender(GraphicsEngine* _graphicsEngine)
{

}

void WhiteEffect::OnCollisionEnter(Object* _other)
{

}

void WhiteEffect::OnCollisionStay(Object* _other)
{

}

void WhiteEffect::OnCollisionExit(Object* _other)
{

}


