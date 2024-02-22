// AnimationEditDlg.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool2.h"
#include "afxdialogex.h"
#include "AnimationEditDlg.h"


// AnimationEditDlg 대화 상자

IMPLEMENT_DYNAMIC(AnimationEditDlg, CDialogEx)

AnimationEditDlg::AnimationEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANIMATION_EDIT_DLG, pParent)
{

}

AnimationEditDlg::~AnimationEditDlg()
{
}

void AnimationEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANIMATION_NAME, this->animationName);
	DDX_Text(pDX, IDC_DELAY_TIME, this->delayTime);
}


void AnimationEditDlg::OnBtnClickedOK()
{
	CDialogEx::OnOK();
}

BEGIN_MESSAGE_MAP(AnimationEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK,&AnimationEditDlg::OnBtnClickedOK)
END_MESSAGE_MAP()


// AnimationEditDlg 메시지 처리기
