#pragma once
#include "ClientHeaders.h"

class ButtonNextPage
	:public Button
{

public:
	ButtonNextPage(ManagerSet* _managers);
	~ButtonNextPage();
	void OnButtonClicked() override;

	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;
};

