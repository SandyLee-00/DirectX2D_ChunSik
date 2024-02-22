#pragma once
#include "ClientHeaders.h"

class ButtonToTitle
	: public Button
{
public:
	ButtonToTitle(ManagerSet* _managers);
	~ButtonToTitle();

	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void OnButtonClicked() override;


};

