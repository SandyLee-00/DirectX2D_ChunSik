#pragma once

#include <string>

// AnimationInfoView 폼 보기

class AnimationInfoView : public CFormView
{
	DECLARE_DYNCREATE(AnimationInfoView)

protected:
	AnimationInfoView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~AnimationInfoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATION_INFO_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	bool AddAnimation();
	void LoadAnimation();
	bool EditAnimation();

	// 현재 선택된 애니메이션의 인덱스를 불러온다.
	int GetAnimationIndex();
	void GetAnimationInfo();
	std::wstring currentAnimName{};
	int currentAnimDelayTime = 0;
	int animationCount = 0;
	int showDelayTime = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox animationList{};
	afx_msg void OnBtnClickedAddAnimation();
	afx_msg void OnBtnClickedDeleteAnimation();
	afx_msg void OnBtnClickedSaveAnimation();
	afx_msg void OnBtnClickedLoadAnimation();
	afx_msg void OnLbtnSelchangeAnimationList();
	afx_msg void OnBtnClickedEditAnimation();
	afx_msg void OnBtnClickedSaveAnimationOne();
};


