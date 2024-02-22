#pragma once
#include "ClientHeaders.h"

class TitleScene
	: public Scene
{
public:
	TitleScene(ManagerSet* _managers);
	~TitleScene();

	void Enter() override;
	void Exit() override;
};

