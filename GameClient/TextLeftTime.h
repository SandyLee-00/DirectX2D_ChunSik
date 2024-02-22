#pragma once
#include "ClientHeaders.h"

class TextLeftTime
	:public Object
{
private:
	// -----------------------------------
	// �뷱�� ��Ʈ const ����

	// ���� �÷��� �ð�
	//const float MAX_PLAYTIME = 10.0f;
	// ������ ���� ���� ���� �ð� �ٲ۴�
	const float MAX_PLAYTIME = 150.0f;

	// �뷱�� ��Ʈ const ����
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

