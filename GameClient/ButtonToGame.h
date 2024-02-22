#pragma once
#include "ClientHeaders.h"

class ButtonToGame
	:public Button
{
public:
	ButtonToGame(ManagerSet* _managers);
	~ButtonToGame();

	virtual void Render(GraphicsEngine* _graphicsEngine) override;

	void OnButtonClicked() override;
};

