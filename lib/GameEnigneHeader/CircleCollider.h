#pragma once
#include "Collider.h"

class Object;
class GraphicsEngine;

/// <summry>
/// CircleCollider Ŭ����
/// ���� �ۼ��� : 2023/07/24
/// ���� �ۼ��� : 2023/08/07
/// �ۼ��� : ����ȯ
/// 
/// ���� �ݶ��̴�
/// <\summry>

class CircleCollider :
    public Collider
{
private:
	float radius;
	
public:
	CircleCollider(Object* owner, float _radius = 1);
	virtual ~CircleCollider();

	virtual bool IsCollision(BoxCollider* _other) override;
	virtual bool IsCollision(CircleCollider* _other) override;
	virtual bool IsCollision(Vector2 _other) override;

	void Update(float _dt = 0) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	float GetRadius() const { return radius; }
	void SetRadius(float val) { radius = val; }

	Vector2 GetMinPoint() override;
	Vector2 GetMaxPoint() override;
};

