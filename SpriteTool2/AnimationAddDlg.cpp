// AnimationAddDlg.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool2.h"
#include "afxdialogex.h"
#include "AnimationAddDlg.h"


// AnimationAddDlg 대화 상자

IMPLEMENT_DYNAMIC(AnimationAddDlg, CDialogEx)

AnimationAddDlg::AnimationAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANIMATION_ADD_DLG, pParent)
{

}

AnimationAddDlg::~AnimationAddDlg()
{
}

void AnimationAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANIMATION_NAME, this->animationName);
	DDX_Text(pDX, IDC_DELAY_TIME, this->delayTime);
}


BEGIN_MESSAGE_MAP(AnimationAddDlg, CDialogEx)
END_MESSAGE_MAP()


// AnimationAddDlg 메시지 처리기
