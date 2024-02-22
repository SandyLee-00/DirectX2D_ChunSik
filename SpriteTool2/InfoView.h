#pragma once

class ExtractedSprite;

// InfoView 폼 보기

class SpriteInfoView : public CFormView
{
	DECLARE_DYNCREATE(SpriteInfoView)

protected:
	SpriteInfoView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SpriteInfoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPRITE_INFO_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	void GetSpriteInfo(ExtractedSprite* _extractedSprite);
	ExtractedSprite* pCurrentExtractedSprite = nullptr;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString spriteName{};
	float spriteX = 0.f;
	float spriteY = 0.f;
	float spriteCx = 0.f;
	float spriteCy = 0.f;
	float spritePx = 0.f;
	float spritePy = 0.f;



	afx_msg void OnClickedSpriteApply();
	afx_msg void OnBnClickedSaveSprite();
	afx_msg void OnBnClickedLoadSprite();
};


