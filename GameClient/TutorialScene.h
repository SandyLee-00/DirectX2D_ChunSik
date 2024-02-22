#pragma once
#include "ClientHeaders.h"

class TutorialScene
	: public Scene
{
public:
	TutorialScene(ManagerSet* _managers);
	~TutorialScene();

	void Enter() override;
	void Exit() override;
};

