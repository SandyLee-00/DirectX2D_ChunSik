// InfoView.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool2.h"
#include "InfoView.h"
#include "SpriteTool2Doc.h"
#include "ExtractedSprite.h"
#include "SpriteTool2View.h"
#include "ResourceManager.h"


// InfoView

IMPLEMENT_DYNCREATE(SpriteInfoView, CFormView)

SpriteInfoView::SpriteInfoView()
	: CFormView(IDD_SPRITE_INFO_VIEW)
{

}

SpriteInfoView::~SpriteInfoView()
{
}

void SpriteInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_CX, this->spriteCx);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_CY, this->spriteCy);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_NAME, this->spriteName);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_PX, this->spritePx);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_PY, this->spritePy);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_X, this->spriteX);
	DDX_Text(pDX, IDC_EXTRACTED_SPRITE_Y, this->spriteY);

	((CSpriteTool2Doc*)GetDocument())->pSpriteInfoView = this;
}

BEGIN_MESSAGE_MAP(SpriteInfoView, CFormView)
	ON_BN_CLICKED(IDC_SPRITE_APPLY, &SpriteInfoView::OnClickedSpriteApply)
	ON_BN_CLICKED(IDC_SAVE_SPRITE, &SpriteInfoView::OnBnClickedSaveSprite)
	ON_BN_CLICKED(IDC_LOAD_SPRITE, &SpriteInfoView::OnBnClickedLoadSprite)
END_MESSAGE_MAP()


// InfoView 진단

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

void SpriteInfoView::GetSpriteInfo(ExtractedSprite* _extractedSprite)
{
	if (_extractedSprite == nullptr)
	{
		return;
	}

	UpdateData(TRUE);

	this->pCurrentExtractedSprite = _extractedSprite;

	this->spriteName = _T("");
	this->spriteName.Append(_extractedSprite->name.c_str());
	this->spriteX = _extractedSprite->left;
	this->spriteY = _extractedSprite->top;
	this->spriteCx = _extractedSprite->right;
	this->spriteCy = _extractedSprite->bottom;
	this->spritePx = _extractedSprite->pivotX;
	this->spritePy = _extractedSprite->pivotY;

	UpdateData(FALSE);
}




// InfoView 메시지 처리기


void SpriteInfoView::OnClickedSpriteApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (this->pCurrentExtractedSprite == nullptr)
	{
		return;
	}
	UpdateData(TRUE);
	this->pCurrentExtractedSprite->name = CT2W(this->spriteName);
	this->pCurrentExtractedSprite->left = this->spriteX;
	this->pCurrentExtractedSprite->top = this->spriteY;
	this->pCurrentExtractedSprite->right = this->spriteCx;
	this->pCurrentExtractedSprite->bottom = this->spriteCy;
	this->pCurrentExtractedSprite->pivotX = this->spritePx;
	this->pCurrentExtractedSprite->pivotY = this->spritePy;
	UpdateData(FALSE);

	((CSpriteTool2Doc*)GetDocument())->pMainView->Invalidate(TRUE);
}


void SpriteInfoView::OnBnClickedSaveSprite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();
		CString tempFileName{};
		tempFileName = dlg.GetPathName();
		pDoc->pResourceManager->SaveSpriteData(tempFileName);	// 한 모션 저장
	}
}


void SpriteInfoView::OnBnClickedLoadSprite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();
		CString tempFileName{};
		tempFileName = dlg.GetPathName();
		pDoc->pResourceManager->SaveSpriteData(tempFileName);	// 한 모션 저장
	}
	((CSpriteTool2Doc*)GetDocument())->pMainView->Invalidate();
}
