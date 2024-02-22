
// SpriteTool2View.h: CSpriteTool2View 클래스의 인터페이스
//

#pragma once

#include "SpriteTool2Doc.h"

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

class ExtractedSprite;
class Sprite;

enum class MOUSE_SELECT_STATE
{
	NONE,
	DRAW_BOX,
	SELECT_BOX,

	END
};

class CSpriteTool2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CSpriteTool2View() noexcept;
	DECLARE_DYNCREATE(CSpriteTool2View)

		// 특성입니다.
public:
	CSpriteTool2Doc* GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CSpriteTool2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void MyInitialize();
	void LoadBitMapByFilePath(const LPCTSTR& _filePath, HINSTANCE _hInst = nullptr);
	/// <summary>
	/// 매개변수로 받아온 point와 박스들의 위치가 겹치는지를 확인
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	ExtractedSprite* IsBoxPosition(CPoint _point);
	void GridByCellCount(const SLICE_PIVOT_INFO& _pivotInfo, int c, float _customX = 0.5f,
		float _customY = 0.5f);

	CD2DPointF GetPivotByInfo(const SLICE_PIVOT_INFO& _pivotInfo, const CD2DRectF& _rect, float _customX = 1,
		float _customY = 1);

private:
	std::vector<std::vector<bool>> visitedPixel{};
	float thisMaxLeft = 0.f, thisMaxRight = 0.f, thisMaxTop = 0.f, thisMaxBottom = 0.f;
	int width = 0, height = 0;

	// 상자를 자르고 이름을 붙일 때 필요한 인덱스와 함수
	std::wstring MakeSpriteName();
	int spriteNameIndex = 0;

	CD2DTextFormat* pTextFormat = nullptr;
	CD2DSolidColorBrush* pBlackBrush = nullptr;


	std::unordered_map<std::wstring, Sprite*> sprites{};
	// 마우스 드래그 rect 위치, pivot 위치
	float rectX = 0.f, rectY = 0.f, rectCx = 0.f, rectCy = 0.f;
	float m_pivotOffsetX = 0.f, pivotOffsetY = 0.f;
	float rectMinInterval = 100.f;	// 상자의 최소 간격

	// 마우스를 조금만 움직여도 상자가 움직이니 살짝 여유를 둘 변수
	float prevSelectedPosX = 0.f, prevSelectedPosY = 0.f;
	float curSelectedPosX = 0.f, curSelectedPosY = 0.f;
	float mouseSelectedPosMinInterval = 500;	
	bool canMoveSmooth = false;	// 마우스가 일정 범위를 넘으면 상자를 원할하게 정교한 위치로 세부 조정할 수 있게 하는 변수

	// 현재 클릭된 상태인지 
	bool isClicked = false;
	// 마우스로 선택된 상자
	ExtractedSprite* pSelectedBox = nullptr;
	// 현재 마우스가 해야할 일
	MOUSE_SELECT_STATE mouseSelectState = MOUSE_SELECT_STATE::DRAW_BOX;

	// 다중 선택 함수 및 변수
	void PushSelectedBox(ExtractedSprite* _box);
	void ClearSelectedBox();
	std::queue<ExtractedSprite*> selectedBoxQueue{};
	int selectedCount = 0;
	bool isShiftDown = false;

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:

	CD2DSolidColorBrush* pGreenBrush = nullptr;

	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNewImage();
};

#ifndef _DEBUG  // SpriteTool2View.cpp의 디버그 버전
//inline CSpriteTool2Doc* CSpriteTool2View::GetDocument() const
//{
//	return reinterpret_cast<CSpriteTool2Doc*>(m_pDocument);
//}
#endif

