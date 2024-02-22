#pragma once

class SpriteAnimation;
class ExtractedSprite;

// AnimationView 폼 보기

class AnimationView : public CFormView
{
	DECLARE_DYNCREATE(AnimationView)

protected:
	AnimationView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~AnimationView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATION_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	SpriteAnimation* pRenderAnimation = nullptr;
	ExtractedSprite* pRenderSprite = nullptr;

	int frame = 0;
	int maxFrame = 1;
	
	CD2DSolidColorBrush* pBlackBrush = nullptr;

	void SetDelayTime(int t);

private:
	int delayTime = 500;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	virtual void OnInitialUpdate();
};


