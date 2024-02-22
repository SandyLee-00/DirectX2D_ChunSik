#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class ButtonToExit : public Button
{
public:
	ButtonToExit(ManagerSet* _managers);
	~ButtonToExit();

	virtual void Render(GraphicsEngine* _graphicsEngine) override;

	void OnButtonClicked() override;
};

