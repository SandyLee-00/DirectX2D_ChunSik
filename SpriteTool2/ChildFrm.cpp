
// ChildFrm.cpp: CChildFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "SpriteTool2.h"

#include "ChildFrm.h"
#include "SpriteEditorView.h"
#include "InfoView.h"
#include "ResourceManager.h"
#include "ExtractedSprite.h"
#include "ControlView.h"
#include "AnimationInfoView.h"
#include "AnimationView.h"
#include "SpriteTool2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame 생성/소멸

CChildFrame::CChildFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	// 프레임의 윈도우 크기 수정
	cs.cx = 1300;
	cs.cy = 900;
	cs.x = 0;
	cs.y = 0;

	return TRUE;
}

// CChildFrame 진단

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

int CChildFrame::OnCreate(LPCREATESTRUCT _lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(_lpCreateStruct) == -1)
	{
		return -1;
	}

	return 0;
}

// CChildFrame 메시지 처리기


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (!this->wndSplitter1.CreateStatic(this, 1, 3))
	{
		TRACE0("Failed to CreateStatic Splitter\n");
		return FALSE;
	}
	int IDpane1 = this->wndSplitter1.IdFromRowCol(0, 0); //왼쪽 윈도우 아이디 접근
	int IDpane2 = this->wndSplitter1.IdFromRowCol(0, 1); //중간 윈도우 아이디 접근
	int IDpane3 = this->wndSplitter1.IdFromRowCol(0, 2); //오른쪽 윈도우 아이디 접근

	if (!wndSplitter2.CreateStatic(&this->wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, IDpane1))
	{
		TRACE0("Failed to CreateStatic Splitter2\n");
		return FALSE;
	}

	if (!this->wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CSpriteTool2View), CSize(800, 500), pContext)
		|| !this->wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(AnimationView), CSize(100, 100), pContext))
	{
		TRACE0("Fail to create Left view");
		return FALSE;
	}

	if (!this->wndSplitter3.CreateStatic(&this->wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, IDpane2))
	{
		TRACE0("Failed to CreateStatic Splitter3\n");
		return FALSE;
	}
	if (!this->wndSplitter3.CreateView(0, 0, RUNTIME_CLASS(SpriteEditorView), CSize(100, 100), pContext))
	{
		TRACE0("Fail to create CSpriteTool2View");
		return FALSE;
	}
	//
	if (!this->wndSplitter3.CreateView(1, 0, RUNTIME_CLASS(SpriteInfoView), CSize(100, 100), pContext))
	{
		TRACE0("Fail to create ControlView");
		return FALSE;
	}

	if (!this->wndSplitter4.CreateStatic(&this->wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, IDpane3))
	{
		TRACE0("Failed to CreateStatic Splitter4");
		return FALSE;
	}
	if (!this->wndSplitter4.CreateView(0, 0, RUNTIME_CLASS(AnimationInfoView), CSize(100, 100), pContext))
	{
		TRACE0("Fail to create AnimationInfoView");
		return FALSE;
	}
	if (!this->wndSplitter4.CreateView(1, 0, RUNTIME_CLASS(ControlView), CSize(100, 100), pContext))
	{
		TRACE0("Fail to create AnimationView");
		return FALSE;
	}

	// splitter 정보 변경 ( 행or 열 , 최대 크기, 최소 크기)
	this->wndSplitter1.SetColumnInfo(0, 800, 20);
	this->wndSplitter1.SetColumnInfo(1, 250, 20);
	this->wndSplitter3.SetRowInfo(0, 500, 10);
	this->wndSplitter4.SetRowInfo(0, 500, 10);

	return TRUE;

	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}
