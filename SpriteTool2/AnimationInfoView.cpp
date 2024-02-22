// AnimationInfoView.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool2.h"
#include "AnimationInfoView.h"
#include "SpriteAnimation.h"
#include "SpriteTool2Doc.h"
#include "SpriteTool2View.h"
#include "AnimationEditDlg.h"
#include "AnimationAddDlg.h"
#include "AnimationView.h"
#include "ResourceManager.h"
#include "ExtractedSprite.h"


// AnimationInfoView

IMPLEMENT_DYNCREATE(AnimationInfoView, CFormView)

AnimationInfoView::AnimationInfoView()
	: CFormView(IDD_ANIMATION_INFO_VIEW)
{

}

AnimationInfoView::~AnimationInfoView()
{
}

void AnimationInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIMATION_LIST, this->animationList);
	DDX_Text(pDX, IDC_EDIT2, this->showDelayTime);

	//((CSpriteTool2Doc*)GetDocument())->pAnimationView = this;
}

BEGIN_MESSAGE_MAP(AnimationInfoView, CFormView)
	ON_BN_CLICKED(IDC_ADD_ANIMATION, &AnimationInfoView::OnBtnClickedAddAnimation)
	ON_BN_CLICKED(IDC_DELETE_ANIMATION, &AnimationInfoView::OnBtnClickedDeleteAnimation)
	ON_BN_CLICKED(IDC_SAVE_ANIMATION, &AnimationInfoView::OnBtnClickedSaveAnimation)
	ON_BN_CLICKED(IDC_LOAD_ANIMATION, &AnimationInfoView::OnBtnClickedLoadAnimation)
	ON_LBN_SELCHANGE(IDC_ANIMATION_LIST, &AnimationInfoView::OnLbtnSelchangeAnimationList)
	ON_BN_CLICKED(IDC_EDIT_ANIMATION, &AnimationInfoView::OnBtnClickedEditAnimation)
	ON_BN_CLICKED(IDC_SAVE_ANIMATION_ONE, &AnimationInfoView::OnBtnClickedSaveAnimationOne)
END_MESSAGE_MAP()


// AnimationInfoView 진단

#ifdef _DEBUG
void AnimationInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AnimationInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#endif
#endif //_DEBUG

bool AnimationInfoView::AddAnimation()
{
	if (((CSpriteTool2Doc*)GetDocument())->pResourceManager->selectedBoxQueue.empty())
	{
		return false;
	}

	AnimationAddDlg dlg{};
	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		this->currentAnimName = CT2W(dlg.animationName);
		this->currentAnimDelayTime = dlg.delayTime;
		UpdateData(FALSE);
	}
	else
	{
		return false;
	}

	SpriteAnimation* pNewAnim = new SpriteAnimation;
	pNewAnim->name = this->currentAnimName;
	pNewAnim->delayTime = this->currentAnimDelayTime;

	while (!((CSpriteTool2Doc*)GetDocument())->pResourceManager->selectedBoxQueue.empty())
	{
		ExtractedSprite* pExSpr = ((CSpriteTool2Doc*)GetDocument())->pResourceManager->selectedBoxQueue.front();
		pNewAnim->sprites.push_back(pExSpr);
		pExSpr->isSelected = false;
		((CSpriteTool2Doc*)GetDocument())->pResourceManager->selectedBoxQueue.pop();
	}

	((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations.push_back(pNewAnim);
	return true;
}

void AnimationInfoView::LoadAnimation()
{
	for (int i = 0; i < this->animationCount; i++)
	{
		this->animationList.DeleteString(0);
	}

	this->animationCount = 0;
	for (int i = 0; i < ((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations.size(); i++)
	{
		this->animationList.InsertString(this->animationCount,
			((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations[this->animationCount]->name.c_str());
		this->animationCount++;
	}
}

bool AnimationInfoView::EditAnimation()
{
	// 현재 ListBox에서 선택된 아이템의 인덱스를 받아오기
	// (만약 선택되어 있지 않다면 -1)
	int curSel = this->animationList.GetCurSel();

	if (curSel == -1)
	{
		MessageBox(_T("선택된 애니메이션이 없습니다."));
		return false;
	}

	AnimationEditDlg dlg{};
	CString cstr{};
	cstr.Append(((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations[curSel]->name.c_str());
	dlg.animationName = cstr;
	dlg.delayTime = ((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations[curSel]->delayTime;
	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);

		this->currentAnimName = CT2W(dlg.animationName);
		this->currentAnimDelayTime = dlg.delayTime;
		SpriteAnimation* pCurAnim = ((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations[curSel];

		pCurAnim->name = this->currentAnimName;
		pCurAnim->delayTime = this->currentAnimDelayTime;
		this->animationList.DeleteString(curSel);
		this->animationList.InsertString(curSel, this->currentAnimName.c_str());

		((CSpriteTool2Doc*)GetDocument())->pAnimationView->SetDelayTime(this->currentAnimDelayTime);
		UpdateData(FALSE);
	}
	else
	{
		return false;
	}

	return true;
}

int AnimationInfoView::GetAnimationIndex()
{
	int curSel = this->animationList.GetCurSel();

	if (curSel == -1)
	{
		MessageBox(_T("선택된 애니메이션이 없습니다."));
		return -1;
	}
	return curSel;
}




void AnimationInfoView::GetAnimationInfo()
{
	int curSel = this->animationList.GetCurSel();

	if (curSel == -1)
	{
		MessageBox(_T("선택된 애니메이션이 없습니다."));
		return;
	}

	UpdateData(TRUE);
	this->showDelayTime= ((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations[curSel]->delayTime;
	UpdateData(FALSE);
}

// AnimationInfoView 메시지 처리기

void AnimationInfoView::OnBtnClickedAddAnimation()
{
	if (!AddAnimation())
	{
		MessageBox(_T("선택된 스프라이트가 없습니다."));
		return;
	}

	this->animationList.InsertString(this->animationCount, this->currentAnimName.c_str());
	this->animationCount++;
}

void AnimationInfoView::OnBtnClickedDeleteAnimation()
{
	// 현재 ListBox에서 선택된 아이템의 인덱스를 받아오기
	// (만약 선택되어 있지 않다면 -1)
	int curSel = this->animationList.GetCurSel();

	if (curSel == -1)
	{
		MessageBox(_T("선택된 스프라이트가 없습니다."));
		return;
	}

	// 현재 선택된 아이템이 있다면
	if (curSel >= 0)
	{
		// 해당 아이템을 제거
		this->animationList.DeleteString(curSel);
	}
	((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations.erase(
		find(((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations.begin(),
			((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations.end(),
			((CSpriteTool2Doc*)GetDocument())->pResourceManager->animations[curSel])
	);
	this->animationCount--;
}

void AnimationInfoView::OnBtnClickedSaveAnimation()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();
		CString tempfilename{};
		tempfilename = dlg.GetPathName();
		pDoc->pResourceManager->SaveAnimationData(tempfilename);
	}
}

void AnimationInfoView::OnBtnClickedLoadAnimation()
{
	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");

	/// 파일 공용컨트롤 대화상자 인스턴스 생성.. 첫번째 인자가 TRUE 이면 읽기 FALSE 이면 쓰기.
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();
		CString tempfilename{};
		tempfilename = dlg.GetPathName();
		pDoc->pResourceManager->LoadAnimationData(tempfilename);
		LoadAnimation();
		pDoc->pAnimationView->pRenderAnimation = nullptr;
	}
}

void AnimationInfoView::OnLbtnSelchangeAnimationList()
{
	CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();

	int curSel = this->animationList.GetCurSel();

	if (curSel == -1)
	{
		return;
	}

	pDoc->pAnimationView->pRenderAnimation = pDoc->pResourceManager->animations[curSel];
	pDoc->pAnimationView->SetDelayTime(pDoc->pResourceManager->animations[curSel]->delayTime);
	GetAnimationInfo();
	pDoc->pAnimationView->frame = 0;
	pDoc->pAnimationView->Invalidate();
}

void AnimationInfoView::OnBtnClickedEditAnimation()
{
	EditAnimation();
}

void AnimationInfoView::OnBtnClickedSaveAnimationOne()
{
	int idx = GetAnimationIndex();

	if (idx == -1)
	{
		return;
	}

	LPCTSTR lpszFilter = _T("텍스트 파일(*.txt)|*.txt|모든파일|*.*||");
	CFileDialog dlg(FALSE, _T(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);

	if (dlg.DoModal() == IDOK)
	{
		CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();
		CString tempfilename{};
		tempfilename = dlg.GetPathName();
		pDoc->pResourceManager->SaveAnimationOneData(tempfilename, idx);
	}
}
