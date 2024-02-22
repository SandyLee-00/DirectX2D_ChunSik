#pragma once
#include "ClientHeaders.h"

class ButtonToCredit
	: public Button
{

public:
	ButtonToCredit(ManagerSet* _managers);
	~ButtonToCredit();

	virtual void Render(GraphicsEngine* _graphicsEngine) override;

	void OnButtonClicked() override;

};

