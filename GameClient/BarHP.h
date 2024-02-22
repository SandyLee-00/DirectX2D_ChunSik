#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

/// <summary>
/// 이서영
/// 
/// parent에 GetHP 해서 HP를 받아온다
/// HP 표시한다 
/// 
/// Bar Object 만들었는데 안썼다
/// HP 칸으로 되어있어서 그냥 다시 만들었다
/// </summary>

class BarHP
	: public Object
{
private:
	Object* parent;

	int MaxHP = 0;
	int HP = 0;

public:
	BarHP(ManagerSet* _managers);
	~BarHP();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetParent(Object* _owner) { parent = _owner; };
	Object* GetParent() { return parent; };

	void SetMaxHP(int _maxHP) { MaxHP = _maxHP; };
};
