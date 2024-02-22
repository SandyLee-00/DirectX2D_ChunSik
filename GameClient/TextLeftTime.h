#pragma once
#include "ClientHeaders.h"

class TextLeftTime
	:public Object
{
private:
	// -----------------------------------
	// 밸런스 시트 const 값들

	// 게임 플레이 시간
	//const float MAX_PLAYTIME = 10.0f;
	// 김정우 빨리 진행 위해 시간 바꾼다
	const float MAX_PLAYTIME = 150.0f;

	// 밸런스 시트 const 값들
	// -----------------------------------

	bool isWorking;
	float playleftSecond;

public:
	TextLeftTime(ManagerSet* _managers);
	~TextLeftTime();

	void Start() override;
	void Update(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;

	float GetPlayleftSecond() const { return playleftSecond; }
	void SetPlayleftSecond(float val) { playleftSecond = val; }
	const float GetMAX_PLAYTIME() const { return MAX_PLAYTIME; }
};

