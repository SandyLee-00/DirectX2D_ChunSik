#pragma once



// SpriteEditorView 폼 보기

class SpriteEditorView : public CFormView
{
	DECLARE_DYNCREATE(SpriteEditorView)

protected:
	SpriteEditorView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SpriteEditorView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPRITE_EDITOR_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CRenderTarget* pRT = nullptr;
	void LoadBitmapByFilePath(LPCTSTR _filePath);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnClickedLoadbmpBtn();

	// type (auto, grid by cell size or count)
	CString typeInfo{};
	virtual void OnInitialUpdate();

	/// <summary>
	/// SliceButton
	/// </summary>
	afx_msg void OnBtnClickedSliceBtn();
	int cellColumn = 0;
	float cellSizeX = 0.f;
	float cellSizeY = 0.f;
	float pivotX = 0.f;
	float pivotY = 0.f;
};


