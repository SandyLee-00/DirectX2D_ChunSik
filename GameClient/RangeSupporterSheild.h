#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// �����Ͱ� �ǵ� Ű�� ������ 
/// ���� ���� ���� / ����𿡰� �ǵ� isOnOff�� true�� �ٲ��ش�.
/// </summary>

class Supporter;
class ShieldToDealer;
class ShieldToGuardian;

class RangeSupporterSheild
	: public Object
{
private:
	// -----------------------------------
	// �뷱�� ��Ʈ const ����

	// ������ �ǵ� ����
	const Vector2 SHEILD_RANGE = Vector2(96.f * 3, 96.f * 3);

	// ������ �ǵ� ��Ÿ��

	// �뷱�� ��Ʈ const ����
	// -----------------------------------

	Supporter* supporter;

	bool isOnOff;
	ShieldToDealer* shieldToDealer;
	ShieldToGuardian* shieldToGuardian;
	Animation* animation = nullptr;
	bool soundFlag;

public:
	RangeSupporterSheild(ManagerSet* _managers);
	~RangeSupporterSheild();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void OnCollisionEnter(Object* _other) override;
	void OnCollisionStay(Object* _other) override;
	void OnCollisionExit(Object* _other) override;

	void SetParent(Supporter* _parent) { supporter = _parent; };
	Supporter* GetParent() { return supporter; };

	void SetOnOff(bool _isOnOff) { isOnOff = _isOnOff; };
	bool GetOnOff() { return isOnOff; };
	ShieldToDealer* GetShieldToDealer() const { return shieldToDealer; }
	void SetShieldToDealer(ShieldToDealer* val) { shieldToDealer = val; }
	ShieldToGuardian* GetShieldToGuardian() const { return shieldToGuardian; }
	void SetShieldToGuardian(ShieldToGuardian* val) { shieldToGuardian = val; }
};

