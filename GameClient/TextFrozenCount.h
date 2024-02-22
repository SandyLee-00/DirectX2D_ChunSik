#pragma once
#include "ClientHeaders.h"

/// <summary>
/// �̼���
/// ��ü ������ HOLD ������ ���͸� ã�Ƽ� ī��Ʈ
/// ī��Ʈ �� ���� �ؽ�Ʈ�� ���
/// 
/// ���� ���� �����ؼ� ��� ���͸� ã�� �κ��� ������ �ȵ�� 
/// </summary>

class TextFrozenCount
	: public Object
{
private:
	bool isWorking;
	int HOLDMonsterCount;

public:
	TextFrozenCount(ManagerSet* _managers);
	~TextFrozenCount();

	void Start() override;
	void Update(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;

	int GetHOLDMonsterCount() const { return HOLDMonsterCount; }
	void SetHOLDMonsterCount(int val) { HOLDMonsterCount = val; }

	void PlusCount();
	void MinusCount();
};
