﻿
// SpriteTool2Doc.cpp: CSpriteTool2Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SpriteTool2.h"
#endif

#include "SpriteTool2Doc.h"

#include <propkey.h>

#include "ResourceManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSpriteTool2Doc

IMPLEMENT_DYNCREATE(CSpriteTool2Doc, CDocument)

BEGIN_MESSAGE_MAP(CSpriteTool2Doc, CDocument)
END_MESSAGE_MAP()


// CSpriteTool2Doc 생성/소멸

CSpriteTool2Doc::CSpriteTool2Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	this->pResourceManager = new ResourceManager;
}

CSpriteTool2Doc::~CSpriteTool2Doc()
{
	delete this->pResourceManager;
}

BOOL CSpriteTool2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSpriteTool2Doc serialization

void CSpriteTool2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSpriteTool2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSpriteTool2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSpriteTool2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSpriteTool2Doc 진단

#ifdef _DEBUG
void CSpriteTool2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpriteTool2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

void CSpriteTool2Doc::SaveSpriteData(const CString& _filePath)
{
	this->pResourceManager->SaveSpriteData(_filePath);
}

#endif //_DEBUG


// CSpriteTool2Doc 명령
