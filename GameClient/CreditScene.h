#pragma once
#include "ClientHeaders.h"

class CreditScene
	: public Scene
{
public:
	CreditScene(ManagerSet* _managers);
	~CreditScene();

	void Enter() override;
	void Exit() override;
	
};

