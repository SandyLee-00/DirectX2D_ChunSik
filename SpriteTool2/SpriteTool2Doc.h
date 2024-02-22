
// SpriteTool2Doc.h: CSpriteTool2Doc 클래스의 인터페이스
//


#pragma once

class ResourceManager;
class CSpriteTool2View;
class SpriteInfoView;
class AnimationView;

class CSpriteTool2Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CSpriteTool2Doc() noexcept;
	DECLARE_DYNCREATE(CSpriteTool2Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CSpriteTool2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

public:
	// 모든 데이터를 관리할 함수와 클래스
	void SaveSpriteData(const CString& _filePath);
	ResourceManager* pResourceManager = nullptr;

	// 메인 뷰의 렌더 타겟
	CRenderTarget* pRT = nullptr;

	// 애니메이션 뷰의 렌더 타겟
	CRenderTarget* pRTAnimationView = nullptr;

	// 메인 뷰 클래스 (메인 이미지가 보이는)
	CSpriteTool2View* pMainView = nullptr;

	// 스프라이트의 정보를 보여줄 뷰 클래스
	SpriteInfoView* pSpriteInfoView = nullptr;

	// 애니메이션 뷰
	AnimationView* pAnimationView = nullptr;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
