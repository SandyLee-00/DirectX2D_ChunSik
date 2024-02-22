#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Guardian;

class ShieldFromGuardian : public Object
{
private:

	// �¿��� ��ư
	bool isOnOff;

	// �ǵ� ���� �ð�
	const float SHIELD_TIME = 6.f;
	float shieldElapseTime;

	// �ǵ尡 ä������
	bool isFull;

	Guardian* guardian;
	// ����� �ִϸ��̼�
	Animation* animation;


	const Vector2 SHEILD_RANGE = Vector2(96.f * 3, 96.f * 3);

public:
	ShieldFromGuardian(ManagerSet* _managers);
	~ShieldFromGuardian();
	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; };
	bool GetOnOff() { return isOnOff; };

	Guardian* GetGuardian() const { return guardian; }
	void SetGuardian(Guardian* val) { guardian = val; }
};

