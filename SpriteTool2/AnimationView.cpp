// AnimationView.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool2.h"
#include "AnimationView.h"
#include "SpriteAnimation.h"
#include "ExtractedSprite.h"
#include "Sprite.h"
#include "SpriteTool2Doc.h"
#include "ResourceManager.h"

// AnimationView

IMPLEMENT_DYNCREATE(AnimationView, CFormView)

AnimationView::AnimationView()
	: CFormView(IDD_ANIMATION_VIEW)
{
	EnableD2DSupport();

	this->pBlackBrush = new CD2DSolidColorBrush(GetRenderTarget(), D2D1::ColorF(D2D1::ColorF::Black));
}

AnimationView::~AnimationView()
{
}

void AnimationView::SetDelayTime(int t)
{
	this->delayTime = t;
	SetTimer(1, this->delayTime, NULL);
}

void AnimationView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	((CSpriteTool2Doc*)GetDocument())->pAnimationView = this;
	((CSpriteTool2Doc*)GetDocument())->pRTAnimationView = m_pRenderTarget;
}

BEGIN_MESSAGE_MAP(AnimationView, CFormView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AnimationView 진단

#ifdef _DEBUG
void AnimationView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AnimationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// AnimationView 메시지 처리기


void AnimationView::OnDraw(CDC* /*pDC*/)
{
	CSpriteTool2Doc* pDoc = (CSpriteTool2Doc*)GetDocument();

	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));

	if (this->pRenderAnimation != nullptr)
	{
		this->maxFrame = (int)this->pRenderAnimation->sprites.size();

		ExtractedSprite* spr = this->pRenderAnimation->sprites[this->frame];
		CD2DBitmap* bitmap = pDoc->pResourceManager->pAnimationViewSprite->pD2DBitmap;
		CD2DSizeF size = bitmap->GetSize();
		CD2DRectF rect1(0, 0, size.width, size.height);
		CD2DRectF rect2(spr->left, spr->top, spr->right, spr->bottom);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(-spr->left, -spr->top));
		m_pRenderTarget->DrawBitmap(bitmap, &rect2, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &rect2);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	m_pRenderTarget->EndDraw();
}


void AnimationView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		this->frame++;
		if (this->frame >= this->maxFrame)
		{
			this->frame %= this->maxFrame;
		}
		Invalidate();
	}
	CFormView::OnTimer(nIDEvent);
}

void AnimationView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	SetTimer(1, this->delayTime, NULL);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
