#pragma once
#include "headers.h"
#include "Component.h"
#include "Matrix.h"

class Object;
class GraphicsEngine;

/// <summry>
/// Tranform 클래스
/// 최초 작성일 : 2023/07/24
/// 최초 작성일 : 2023/07/24
/// 작성자 : 김형환
/// 
/// 오브젝트의 Transform 정보를 가지고 있는 클래스
/// 위치, 크기, 회전 등의 정보를 가지고 있고 이를 변환 가능
/// 
/// !!!
/// 모든 오브젝트는 이 Component가 있어야 한다 반드시
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
	// TRS 함수
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

