#pragma once
#include "ClientDefines.h"
#include "ClientHeaders.h"

/// <summary>
/// �̼���
/// 
/// �� ǥ���ϱ� ���ؼ� ������ ������Ʈ
/// ��� �׸� �� �ᵵ �ɵ�
/// </summary>

class BackGroundObject
	: public Object
{
private:
	std::string printString;
	int maxPage;
	int currentPage;

public:
	BackGroundObject(ManagerSet* _managers);
	virtual ~BackGroundObject();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void FinalUpdate(float _deltaTime) override;
	virtual void Render(GraphicsEngine* _graphicsEngine) override;
	virtual void DebugRender(GraphicsEngine* _graphicsEngine) override;

	void SetPrintString(std::string _printString) { printString = _printString; }
	std::string GetPrintString() { return printString; }

	void SetMaxPage(int _maxPage) { maxPage = _maxPage; }
	int GetMaxPage() { return maxPage; }

	void SetCurrentPage(int _currentPage) { currentPage = _currentPage; }
	int GetCurrentPage() { return currentPage; }

};

