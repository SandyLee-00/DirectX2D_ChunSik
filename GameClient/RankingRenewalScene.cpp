#include "RankingRenewalScene.h"
#include "RankingScene.h"
#include "MainGameScene.h"

RankingRenewalScene::RankingRenewalScene(ManagerSet* _managers)
	: Scene(_managers)
	, outputText("·©Å· ÁøÀÔ!")
	, outputTime(0.f)
{

}

RankingRenewalScene::~RankingRenewalScene()
{

}

void RankingRenewalScene::Enter()
{
	DeleteAllObjects();
	SoundManager::GetInstance()->Play(SoundManager::SCENEEFFECT, SoundManager::SOUNDRANKIN);
}

void RankingRenewalScene::Exit()
{
	//DeleteAllObjects();

}

void RankingRenewalScene::Update(float _dt)
{
	Scene::Update(_dt);

	this->outputTime += _dt;

	if (outputTime >= 2.f)
	{
		outputTime = 0.f;
		this->managers->GetSceneManager()->ChangeScene("RankingScene");
	}
}

void RankingRenewalScene::Render(GraphicsEngine* _graphicsEngine)
{
	_graphicsEngine->ChangeFontSize(140.f);
	_graphicsEngine->DrawString(610, 472, this->outputText);
}
