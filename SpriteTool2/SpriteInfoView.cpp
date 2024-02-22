// SpriteInfoView.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool.h"
#include "SpriteInfoView.h"


// SpriteInfoView

IMPLEMENT_DYNCREATE(SpriteInfoView, CFormView)

SpriteInfoView::SpriteInfoView()
	: CFormView(IDD_SPRITEINFOVIEW)
{

}

SpriteInfoView::~SpriteInfoView()
{
}

void SpriteInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(SpriteInfoView, CFormView)
END_MESSAGE_MAP()


// SpriteInfoView 진단

#ifdef _DEBUG
void SpriteInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SpriteInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SpriteInfoView 메시지 처리기
