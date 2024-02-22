#pragma once
#include "afxdialogex.h"


// AnimationAddDlg 대화 상자

class AnimationAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AnimationAddDlg)

public:
	AnimationAddDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AnimationAddDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATION_ADD_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString animationName{};
	int delayTime = 0;
};
