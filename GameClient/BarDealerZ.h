#pragma once
#include "ClientHeaders.h"
#include "ClientDefines.h"

class Monster;

class BarDealerZ
	: public Object
{
private:
	Object* parent;
	std::vector<Monster*> checkedMonsters; // 이미 검사한 몬스터들의 리스트

	const int MaxZ = 5;
	int Z;

public:
	BarDealerZ(ManagerSet* _managers);
	~BarDealerZ();

	void Start() override;
	void Update(float _deltaTime) override;
	void FinalUpdate(float _deltaTime) override;
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetParent(Object* _parent) { parent = _parent; };
	Object* GetParent() { return parent; };

	int GetZ() const { return Z; }
	void SetZ(int val) { Z = val; }
	const int GetMaxZ() const { return MaxZ; }
	void SubZ();
};

