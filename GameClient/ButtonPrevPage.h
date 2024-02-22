#pragma once
#include "ClientHeaders.h"

class ButtonPrevPage
	:public Button
{

public:
	ButtonPrevPage(ManagerSet* _managers);
	~ButtonPrevPage();
	void OnButtonClicked() override;

	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;
};

