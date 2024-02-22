#include "Animation.h"
#include "ManagerSet.h"
#include "Object.h"
#include "Animator.h"

Animation::Animation(Object* _owner)
	: Component(CALL_ORDER::ANIMATOR, "Animation", _owner)
	, isPlay(true)
	, spriteObj(nullptr)
	, ani(nullptr)
	, frameAnimation(0.0f)
	, getFrame(0.0f)
	, posX(0)
	, posY(0)
	, thisSprite(0)
	, offset{ 0,0 }
{
	ani = new Animator();
	//ani->GetAnimationInfo(imagePath, txtPath, name, thisSprite);
	owner = _owner;
	nowMotion = 0;
	nowSprite = 0;
	gotNum = 0;
}

Animation::~Animation()
{
	delete this->spriteObj;
	delete this->ani;
}

void Animation::Update(float _dt)
{
	getFrame += _dt;
	if (isPlay)
	{
		//TimeManager* tm = this->owner->GetManagers()->GetTimeManager();
		if (getFrame >= frameAnimation)
		{
			getFrame = 0;
// 			if (spriteObj->motionNum <= nowMotion)
// 			{
// 				nowMotion = 0;
// 				nowSprite = 0;
// 			}

			nowSprite++;

			if (spriteObj->Motions[nowMotion].SpriteNum <= nowSprite)
			{
				nowSprite = 0;
			}
		}
	}
	else
	{
		nowMotion = 0;
		nowSprite = 0;
	}
}

void Animation::Render(GraphicsEngine* _graphicsEngine)
{
	//돌아가는 애니메이션
	_graphicsEngine->DrawSpriteAni(name, spriteObj->Motions[nowMotion].motionSprites[nowSprite], thisSprite, (float)posX + GetOffset().x, (float)posY + GetOffset().y);
}

//몇번째 그림을 데려올건지, mfc 파일 경로, 이름(안중요하지만 겹치지않게), 위치x, 위치y
void Animation::SetSpriteRes( int _getIndex,
	std::wstring _txtPath, std::string _name,int _x,int _y)
{	
	if (gotNum != _getIndex)
	{
		Init();
		gotNum = _getIndex;
	}
	thisSprite = _getIndex;
	txtPath = _txtPath;
	//imagePath = _imagePath;
	name = _name;
	if (spriteObj != nullptr)
	{
		delete spriteObj;
	}
	spriteObj = ani->GetAnimationInfo(owner->GetManagers(), txtPath, name, thisSprite);
	frameAnimation = ani->GetFrame();
	posX = _x;
	posY = _y;

}

//플레이
void Animation::Play()
{
	isPlay = true;
}

//멈춰!
void Animation::Stop(int _index)
{
	isPlay = false;
	nowSprite = _index;
}
void Animation::Init()
{
	delete spriteObj;
	spriteObj = nullptr;
	nowMotion = 0;
	nowSprite = 0;
}
