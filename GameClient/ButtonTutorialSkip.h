#pragma once
#include "ClientHeaders.h"

class ButtonTutorialSkip
	: public Button
{
public:
	ButtonTutorialSkip(ManagerSet* _managers);
	~ButtonTutorialSkip();

	void OnButtonClicked() override;

	virtual void Render(GraphicsEngine* _graphicsEngine) override;
};

