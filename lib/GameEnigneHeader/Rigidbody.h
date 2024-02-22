#pragma once
#include "Component.h"

/// <summary>
/// Rigidbody Ŭ����
/// ���� �ۼ��� : 2023/08/02
/// ���� �ۼ��� : 2023/08/02
/// �ۼ��� : ����ȯ
/// 
/// ���� ������ ���� ��ü Ŭ����
/// ���� ȸ������ ���� �̵� �� �߷¿� ���� ������ ����
/// </summary>

class Rigidbody
	: public Component
{
private:
	Vector2 velocity;
	float mass;
	float iMass;
	Vector2 force;
	bool isGravity;
	float gravity;

public:
	Rigidbody(Object* owner);
	virtual ~Rigidbody();

	void Update(float _dt = 0) override;
	void LateUpdate() override {};
	void Render(GraphicsEngine* _graphicsEngine) override;

	void ApplyForce();

	float GetMass() const { return mass; }
	void SetMass(float _val);
};

