#pragma once
#include "Component.h"

/// <summary>
/// Rigidbody 클래스
/// 최초 작성일 : 2023/08/02
/// 최초 작성일 : 2023/08/02
/// 작성자 : 김형환
/// 
/// 물리 구현을 위한 강체 클래스
/// 현재 회전없이 선형 이동 및 중력에 의한 물리만 구현
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

