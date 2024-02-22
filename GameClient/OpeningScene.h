#pragma once
#include "ClientHeaders.h"

class SoundManager;

class OpeningScene
	: public Scene
{
public:
	OpeningScene(ManagerSet* _managers);
	~OpeningScene();

	void Enter() override;
	void Exit() override;
};

