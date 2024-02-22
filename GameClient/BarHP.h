#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// �̼���
/// 
/// parent�� GetHP �ؼ� HP�� �޾ƿ´�
/// HP ǥ���Ѵ� 
/// 
/// Bar Object ������µ� �Ƚ��
/// HP ĭ���� �Ǿ��־ �׳� �ٽ� �������
/// </summary>

class BarHP
	: public Object
{
private:
	Object* parent;

	int MaxHP = 0;
	int HP = 0;

public:
	BarHP(ManagerSet* _managers);
	~BarHP();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetParent(Object* _owner) { parent = _owner; };
	Object* GetParent() { return parent; };

	void SetMaxHP(int _maxHP) { MaxHP = _maxHP; };
};
