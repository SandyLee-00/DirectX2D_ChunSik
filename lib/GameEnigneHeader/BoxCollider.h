#pragma once
#include "Collider.h"

class Object;

/// <summry>
/// BoxCollider 클래스
/// 최초 작성일 : 2023/07/24
/// 최초 작성일 : 2023/08/07
/// 작성자 : 김형환
/// 
/// 박스 형태의 콜라이더
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

