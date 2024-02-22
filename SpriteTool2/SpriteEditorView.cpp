// SpriteEditorView.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool2.h"
#include "SpriteEditorView.h"
#include "SpriteTool2Doc.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "AnimationView.h"
#include "SpriteTool2View.h"




// SpriteEditorView

IMPLEMENT_DYNCREATE(SpriteEditorView, CFormView)

SpriteEditorView::SpriteEditorView()
	: CFormView(IDD_SPRITE_EDITOR_VIEW)
{

}

SpriteEditorView::~SpriteEditorView()
{
}

void SpriteEditorView::LoadBitmapByFilePath(LPCTSTR _filePath)
{
	HINSTANCE hResInstance = AfxGetResourceHandle();

	CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();

	// 계속해서 초기화해서 새로운 이미지 불러오기
	pDoc->pResourceManager->sprites.clear();

	m_pRenderTarget = pDoc->pRT;
	Sprite* pSprite1 = new Sprite;
	pSprite1->pD2DBitmap = new CD2DBitmap(m_pRenderTarget, _filePath, CD2DSizeU(0, 0), TRUE);
	pSprite1->pD2DBitmap->Create(m_pRenderTarget);
	AfxSetResourceHandle(hResInstance);

	// 애니메이션 뷰용 비트맵을 또 만들어야 함.
	m_pRenderTarget = pDoc->pRTAnimationView;
	Sprite* pSprite2 = new Sprite;
	pSprite2->pD2DBitmap = new CD2DBitmap(m_pRenderTarget, _filePath, CD2DSizeU(0, 0), TRUE);
	pSprite2->pD2DBitmap->Create(m_pRenderTarget);
	AfxSetResourceHandle(hResInstance);

	CD2DSizeF size = pSprite1->pD2DBitmap->GetSize();
	CD2DRectF rect(0.0f, 0.0f, size.width, size.height);
	pDoc->pResourceManager->sprites.insert({ L"test",pSprite1 });
	// document의 메인 스프라이트 초기화
	pDoc->pResourceManager->pMainSprite = pSprite1;
	// doucment의 애니메이션 뷰 스프라이트 초기화
	pDoc->pResourceManager->pAnimationViewSprite = pSprite2;

	m_pRenderTarget = nullptr;
}

void SpriteEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CELL_COLUMN, this->cellColumn);
	DDX_Text(pDX, IDC_PX_EDIT, this->pivotX);
	DDX_Text(pDX, IDC_PY_EDIT, this->pivotY);
}



void SpriteEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// 대화 상자가 출력될 떄 초기화하는 곳.

	// 아래의 초기화는 ComboBox가 아무것도 선택되지 않는 것을 방지하기위해 초기화하는 코드
	((CComboBox*)GetDlgItem(IDC_PIVOT_COMBO))->SetCurSel(0);
}



BEGIN_MESSAGE_MAP(SpriteEditorView, CFormView)
	ON_BN_CLICKED(IDC_LOADBMP_BTN, &SpriteEditorView::OnBtnClickedLoadbmpBtn)
	ON_BN_CLICKED(IDC_SLICE_BTN, &SpriteEditorView::OnBtnClickedSliceBtn)
END_MESSAGE_MAP()


// SpriteEditorView 진단

#ifdef _DEBUG
void SpriteEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SpriteEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SpriteEditorView 메시지 처리기

afx_msg void SpriteEditorView::OnBtnClickedSliceBtn()
{
	// Slice Button

	CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();
	// UpdateData가 없어도 index는 잘 불러옴
	UpdateData(TRUE);

	SLICE_PIVOT_INFO slicePivotInfoIdx = (SLICE_PIVOT_INFO)((CComboBox*)GetDlgItem(IDC_PIVOT_COMBO))->GetCurSel();
	pDoc->pMainView->GridByCellCount(slicePivotInfoIdx, this->cellColumn, this->pivotX, this->pivotY);
	
	UpdateData(FALSE);
}

afx_msg void SpriteEditorView::OnBtnClickedLoadbmpBtn()
{
	LPCTSTR ll = { _T("Image Files(*.bmp;*.png;*.jpg;*.jpeg||)") };
	CFileDialog dlg(TRUE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ll);
	if (dlg.DoModal() == IDOK)
	{
		GetDocument();
		CString tempFilePath{};

		// 메인 스프라이트의 이름을 확장자 빼고 설정
		{
			std::wstring name = CT2W(dlg.GetFileName());

			int idx = (int)name.size() - 1;
			while (name[idx] != '.')
			{
				name.pop_back();
				idx--;
			}
			name.pop_back();

			((CSpriteTool2Doc*)GetDocument())->pResourceManager->pMainSpriteName = name;
		}

		tempFilePath = dlg.GetPathName();
		// 파일 경로를 알았으니 파일을 불러와야 함.
		LoadBitmapByFilePath(tempFilePath);

		((CSpriteTool2Doc*)GetDocument())->pMainView->Invalidate(TRUE);
		((CSpriteTool2Doc*)GetDocument())->pAnimationView->Invalidate(TRUE);
	}
}