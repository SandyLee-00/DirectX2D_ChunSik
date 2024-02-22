#pragma once
#include "ClientHeaders.h"

class ButtonToRanking
: public Button
{
public:
	ButtonToRanking(ManagerSet* _managers);
	~ButtonToRanking();

	virtual void Render(GraphicsEngine* _graphicsEngine) override;

	void OnButtonClicked() override;

};

