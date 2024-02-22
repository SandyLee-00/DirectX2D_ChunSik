#pragma once
#include "ClientHeaders.h"

class ButtonOpeningSkip
	:public Button
{

public:
	ButtonOpeningSkip(ManagerSet* _managers);
	~ButtonOpeningSkip();
	void OnButtonClicked() override;

	virtual void Render(GraphicsEngine* _graphicsEngine) override;

	void DebugRender(GraphicsEngine* _graphicsEngine) override;
};

