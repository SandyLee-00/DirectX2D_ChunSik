#pragma once
#include "Object.h"
#include "Vector2.h"

/// <summary>
/// �̼���
/// 
/// �� ǥ���ϱ� ���ؼ� ������ ������Ʈ
/// ��� �׸� �� �ᵵ �ɵ�
/// </summary>

class EmptyObject
	: public Object
{
private:
	std::string printString;

public:
	EmptyObject(ManagerSet* _managers);
	virtual ~EmptyObject();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void FinalUpdate(float _deltaTime) override;
	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetPrintString(std::string _printString) { printString = _printString; }
	std::string GetPrintString() { return printString; }

};

