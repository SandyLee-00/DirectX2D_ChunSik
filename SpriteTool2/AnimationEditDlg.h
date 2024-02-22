#pragma once
#include "afxdialogex.h"


// AnimationEditDlg 대화 상자

class AnimationEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AnimationEditDlg)

public:
	AnimationEditDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AnimationEditDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATION_EDIT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString animationName{};
	int delayTime = 0;
	afx_msg void OnBtnClickedOK();
};
