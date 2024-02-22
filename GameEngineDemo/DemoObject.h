#pragma once
#include "Object.h"
#include "Vector2.h"
#include "BigInt.h"

class BoxCollider;

class DemoObject
	: public Object
{
private:
	BigInt demoint;
public:
	bool movable;
	DemoObject(ManagerSet* _manager);
	~DemoObject();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	//void OnCollisionEnter(const Object* _other) override;
	//void OnCollisionStay(const Object* _other) override;
	//void OnCollisionExit(const Object* _other) override;
};
