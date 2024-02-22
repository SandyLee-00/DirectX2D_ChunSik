#pragma once
#include "headers.h"
#include "Component.h"
#include "Matrix.h"

class Object;
class GraphicsEngine;

/// <summry>
/// Tranform Ŭ����
/// ���� �ۼ��� : 2023/07/24
/// ���� �ۼ��� : 2023/07/24
/// �ۼ��� : ����ȯ
/// 
/// ������Ʈ�� Transform ������ ������ �ִ� Ŭ����
/// ��ġ, ũ��, ȸ�� ���� ������ ������ �ְ� �̸� ��ȯ ����
/// 
/// !!!
/// ��� ������Ʈ�� �� Component�� �־�� �Ѵ� �ݵ��
/// !!!
/// <\summry>
/// 

class Transform
	: public Component
{
private:
	Matrix transformationMatrix;

public:
	Transform(Object* owner, Vector2 _where = { 0,0 });
	~Transform();

	void Update(float _dt = 0) override {} ;
	void Render(GraphicsEngine* _graphicsEngine) override {};
	void DebugRender(GraphicsEngine* _graphicsEngine) override {};
	virtual void LateUpdate() override {};
	// TRS �Լ�
	void Translation(const Vector2& _distance);
	void SetPosition(const Vector2& _distance);
	void SetRotation(float _angle, int _axis = 3);
	void SetRotation(float _angle, const Vector2& _center, int _axis = 3);
	void SetScale(const Vector2& _scale);
	void SetScale(const Vector2& _scale, const Vector2& _center);

	void SetTransformationMatrix(Matrix val) { transformationMatrix = val; }
	Matrix GetTransformationMatrix() const { return transformationMatrix; }

	// Getter
	Vector2 GetPosition() const;
	Vector2 GetScale() const;
	float GetRotation(int axis = 3) const;
};

