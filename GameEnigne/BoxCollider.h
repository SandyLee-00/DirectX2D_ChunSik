#pragma once
#include "Collider.h"

class Object;

/// <summry>
/// BoxCollider Ŭ����
/// ���� �ۼ��� : 2023/07/24
/// ���� �ۼ��� : 2023/08/07
/// �ۼ��� : ����ȯ
/// 
/// �ڽ� ������ �ݶ��̴�
/// <\summry>
/// 

class BoxCollider :
    public Collider
{
private:
	std::vector<Vector2> localVertices;
	std::vector<Vector2> globalVertices;

public:
	BoxCollider(Object* _owner);
    virtual ~BoxCollider();

	virtual bool IsCollision(BoxCollider* _other) override;
	virtual bool IsCollision(CircleCollider* _other) override;
	virtual bool IsCollision(Vector2 _other) override;

	void Update(float _dt = 0) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetSize(Vector2 _size = {100, 100});
	void SetSize(float _width, float _height);
	void SetSize(int _width, int _height);

	Vector2 GetSize();
	float GetWidth();
	float GetHeight();

	std::vector<Vector2> GetLocalVertices() const { return localVertices; }
	void SetLocalVertices(std::vector<Vector2> val) { localVertices = val; }

	std::vector<Vector2> GetGlobalVertices() const { return globalVertices; }
	void SetGlobalVertices(std::vector<Vector2> val) { globalVertices = val; }

	Vector2 GetMinPoint() override;
	Vector2 GetMaxPoint() override;
};

