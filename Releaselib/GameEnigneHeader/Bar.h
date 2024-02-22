#pragma once
#include "Object.h"
#include "Vector2.h"

class Bar
	: public Object
{
protected:
	// 	Sprite* BackgroundImage;
	// 	Sprite* FillAreaImage;
	float value;

	Object* parent;
	Vector2 offset;
	Vector2 size;

public:
	Bar(ManagerSet* _manager);
	~Bar();
	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void FinalUpdate(float _deltaTime) override;
	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;
	
	void SetValue(float _value) { value = _value; }
	float GetValue() const { return value; }

	void SetParent(Object* _parent) { parent = _parent; }
	void SetOffset(Vector2 _offset) { offset = _offset; }
	void SetSize(Vector2 _size) { size = _size; }
};

