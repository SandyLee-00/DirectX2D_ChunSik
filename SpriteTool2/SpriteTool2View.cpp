
// SpriteTool2View.cpp: CSpriteTool2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SpriteTool2.h"
#endif

#include "SpriteTool2Doc.h"
#include "SpriteTool2View.h"
#include "InfoView.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "ExtractedSprite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static int animationGroup = 0;
static int infoAreaHeight = 40;

// CSpriteTool2View

IMPLEMENT_DYNCREATE(CSpriteTool2View, CView)

BEGIN_MESSAGE_MAP(CSpriteTool2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_NEW_IMAGE, &CSpriteTool2View::OnNewImage)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CSpriteTool2View 생성/소멸

CSpriteTool2View::CSpriteTool2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	MyInitialize();

}

CSpriteTool2View::~CSpriteTool2View()
{
}

BOOL CSpriteTool2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSpriteTool2View 그리기

void CSpriteTool2View::OnDraw(CDC* /*pDC*/)
{
	CSpriteTool2Doc* pDoc = GetDocument();
	pDoc->pRT = m_pRenderTarget;
	pDoc->pMainView = this;

	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Coral));
	if (pDoc->pResourceManager->sprites.find(L"test") != pDoc->pResourceManager->sprites.end())
	{
		Sprite* spr = pDoc->pResourceManager->sprites[L"test"];
		CD2DSizeF size = spr->pD2DBitmap->GetSize();
		CD2DRectF rect(0.0f, 0.0f, size.width, size.height);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
		m_pRenderTarget->DrawBitmap(spr->pD2DBitmap, &rect);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	m_pRenderTarget->DrawRectangle({ this->rectX,this->rectY,this->rectCx,this->rectCy }, this->pGreenBrush);

	for (const auto& extractBox : GetDocument()->pResourceManager->extractedSprites)
	{
		extractBox->Render(m_pRenderTarget);
	}

	m_pRenderTarget->EndDraw();
}


// CSpriteTool2View 인쇄

BOOL CSpriteTool2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSpriteTool2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSpriteTool2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSpriteTool2View 진단

#ifdef _DEBUG
void CSpriteTool2View::AssertValid() const
{
	CView::AssertValid();
}

void CSpriteTool2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


void CSpriteTool2View::MyInitialize()
{
	EnableD2DSupport();

	this->pBlackBrush = new CD2DSolidColorBrush(GetRenderTarget(), D2D1::ColorF(D2D1::ColorF::Black));
	this->pGreenBrush = new CD2DSolidColorBrush(GetRenderTarget(), D2D1::ColorF(D2D1::ColorF::Green));
	this->pTextFormat = new CD2DTextFormat(GetRenderTarget(), _T("Verdana"), 50);
	this->pTextFormat->Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->pTextFormat->Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void CSpriteTool2View::LoadBitMapByFilePath(const LPCTSTR& _filePath, HINSTANCE _hInst /*= nullptr*/)
{
	HINSTANCE hResInstance = AfxGetResourceHandle();

	Sprite* pSprite = new Sprite();
	pSprite->pD2DBitmap = new CD2DBitmap(m_pRenderTarget, _filePath, CD2DSizeU(0, 0), TRUE);

	pSprite->pD2DBitmap->Create(m_pRenderTarget);

	AfxSetResourceHandle(hResInstance);

	CD2DSizeF size = pSprite->pD2DBitmap->GetSize();
	CD2DRectF rect(0.0f, 0.0f, size.width, size.height);
	this->sprites.insert({ L"test", pSprite });
	Invalidate();
}

ExtractedSprite* CSpriteTool2View::IsBoxPosition(CPoint _point)
{
	// 거꾸로 순회 : 마지막에 그린(가장 최근에 그린) 상자를 선택할 수 있게

	for (auto iter = GetDocument()->pResourceManager->extractedSprites.rbegin();
		iter != GetDocument()->pResourceManager->extractedSprites.rend(); ++iter)
	{
		auto c = *iter;

		int x = _point.x, y = _point.y;
		if (x < c->left) continue;
		if (x > c->right) continue;

		// 아래로갈수록 y값이 커짐
		if (y > c->bottom) continue;
		if (y < c->top) continue;
		return c;
	}
	return nullptr;
}

void CSpriteTool2View::GridByCellCount(const SLICE_PIVOT_INFO& _pivotInfo, int c,
	float _customX /*= 0.5f*/, float _customY /*= 0.5f*/)
{
	if (GetDocument()->pResourceManager->pMainSprite == nullptr)
	{
		MessageBox(_T("메인 이미지가 없습니다."));
		return;
	}
	// Grid by cell count
	CD2DSizeF size = GetDocument()->pResourceManager->pMainSprite->pD2DBitmap->GetSize();
	CD2DRectF rectangle(0.0f, 0.0f, size.width, size.height);

	float boxWidth = size.width / c;
	float boxHeight = size.height;

	float boxPositionToDrawX = 0;
	float boxPositionToDrawY = 0;
	int count = c;
	for (int i = 0; i < count; i++)
	{
		CD2DPointF pivot = GetPivotByInfo(_pivotInfo, { boxPositionToDrawX, boxPositionToDrawY,
			boxPositionToDrawX + boxWidth, boxPositionToDrawY + boxHeight }, _customX, _customY);
		ExtractedSprite* box = new ExtractedSprite(boxPositionToDrawX, boxPositionToDrawY, boxPositionToDrawX
			+ boxWidth, boxPositionToDrawY + boxHeight, pivot.x, pivot.y);
		box->name = MakeSpriteName();
		GetDocument()->pResourceManager->extractedSprites.push_back(box);
		boxPositionToDrawX = ((i + 1) % c) * boxWidth;
		boxPositionToDrawY = ((i + 1) / c) * boxHeight;
	}
	Invalidate();
}

CD2DPointF CSpriteTool2View::GetPivotByInfo(const SLICE_PIVOT_INFO& _pivotInfo, const CD2DRectF& _rect,
	float _customX /*= 1*/, float _customY /*= 1*/)
{
	CD2DPointF returnPivot{};

	switch (_pivotInfo)
	{
		case SLICE_PIVOT_INFO::CENTER:
		{
			returnPivot.x = 0.5f;
			returnPivot.y = 0.5f;
		}
		break;
		case SLICE_PIVOT_INFO::TOP_LEFT:
		{
			returnPivot.x = 0.f;
			returnPivot.y = 0.f;
		}
		break;
		case SLICE_PIVOT_INFO::TOP:
		{
			returnPivot.x = 0.5f;
			returnPivot.y = 0.f;
		}
		break;
		case SLICE_PIVOT_INFO::TOP_RIGHT:
		{
			returnPivot.x = 1.f;
			returnPivot.y = 0.f;
		}
		break;
		case SLICE_PIVOT_INFO::LEFT:
		{
			returnPivot.x = 0.f;
			returnPivot.y = 0.5f;
		}
		break;
		case SLICE_PIVOT_INFO::RIGHT:
		{
			returnPivot.x = 1.f;
			returnPivot.y = 0.5f;
		}
		break;
		case SLICE_PIVOT_INFO::BOTTOM_LEFT:
		{
			returnPivot.x = 0.f;
			returnPivot.y = 1.f;
		}
		break;
		case SLICE_PIVOT_INFO::BOTTOM:
		{
			returnPivot.x = 0.5f;
			returnPivot.y = 1.f;
		}
		break;
		case SLICE_PIVOT_INFO::BOTTOM_RIGHT:
		{
			returnPivot.x = 1.f;
			returnPivot.y = 1.f;
		}
		break;
		case SLICE_PIVOT_INFO::CUSTOM:
		{
			// coustom pivot은 비율에 따라 결정

			returnPivot.x = _customX;
			returnPivot.y = _customY;
		}
		break;
		default:
			break;
	}
	return returnPivot;
}

std::wstring CSpriteTool2View::MakeSpriteName()
{
	std::wstring ret = GetDocument()->pResourceManager->pMainSpriteName;
	std::wstring idx = std::to_wstring(this->spriteNameIndex);
	ret += '_';
	ret += idx;
	this->spriteNameIndex++;
	return ret;
}

void CSpriteTool2View::PushSelectedBox(ExtractedSprite* _box)
{
	// 처음 다중 선택할 경우 이전에 선택되어 있던 0번째부터 큐에 추가 후 지금 선택한 상자를 큐에 추가

	GetDocument()->pResourceManager->selectedBoxQueue.push(_box);
	this->selectedCount++;
}

void CSpriteTool2View::ClearSelectedBox()
{
	while (!GetDocument()->pResourceManager->selectedBoxQueue.empty())
	{
		GetDocument()->pResourceManager->selectedBoxQueue.front()->isSelected = false;
		GetDocument()->pResourceManager->selectedBoxQueue.pop();
	}
}

CSpriteTool2Doc* CSpriteTool2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	CRuntimeClass* cl = m_pDocument->GetRuntimeClass();
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpriteTool2Doc)));
	return (CSpriteTool2Doc*)m_pDocument;
}


// CSpriteTool2View 메시지 처리기


void CSpriteTool2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CSpriteTool2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!this->isClicked)
	{
		this->isClicked = true;

		// shift가 안 눌려있을 경우 queue를 초기화 함.
		if (this->isShiftDown == false)
		{
			ClearSelectedBox();
		}

		// 이미 선택되어 있을 경우 Selected 를 false로 바꾸어줌
		if (this->pSelectedBox != nullptr)
		{
			// 처음 shift를 눌렀을 경우 이전 박스와 현재 박스 모두 queue에 넣어주어야 한다.
			// 이 코드는 이전 박스만 넣어준다.
			if (this->selectedCount == 0 && this->isShiftDown == true)
			{
				PushSelectedBox(this->pSelectedBox);
			}

			// 다중 선택 옵션이 아닐 경우 상자의 selected를 꺼준다.
			if (this->isShiftDown == false)
				this->pSelectedBox->isSelected = false;
		}
		this->pSelectedBox = nullptr;

		// 마우스의 위치에 상자가 있는지 확인
		ExtractedSprite* rect = IsBoxPosition(point);

		// 상자가 있을 경우 아래의 블록 실행
		if (rect != nullptr)
		{
			this->pSelectedBox = rect;
			this->pSelectedBox->isSelected = true;

			this->prevSelectedPosX = (float)point.x;
			this->prevSelectedPosY = (float)point.y;
			this->canMoveSmooth = false;

			// 선택된 상자 queue에 추가
			PushSelectedBox(this->pSelectedBox);

			// 선택된 상자의 정보를 infoView에 출력
			GetDocument()->pSpriteInfoView->GetSpriteInfo(this->pSelectedBox);

			this->mouseSelectState = MOUSE_SELECT_STATE::SELECT_BOX;
			return;
		}

		// 선택되어 있지 않을 경우 DrawBox 모드로 설정
		this->mouseSelectState = MOUSE_SELECT_STATE::DRAW_BOX;
		this->rectX = (float)point.x;
		this->rectY = (float)point.y;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CSpriteTool2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (this->isClicked)
	{
		switch (this->mouseSelectState)
		{
			case MOUSE_SELECT_STATE::DRAW_BOX:
			{
				this->rectCx = (float)point.x;
				this->rectCy = (float)point.y;
			}
			break;
			case MOUSE_SELECT_STATE::SELECT_BOX:
			{
				if (this->pSelectedBox == nullptr)
					break;

				// 마우스를 조금만 움직였을 경우 아직 움직이지 않게 하기 위해 여유를 둔다
				this->curSelectedPosX = (float)point.x;
				this->curSelectedPosY = (float)point.y;

				float curToPrevX = this->curSelectedPosX - this->prevSelectedPosX;
				float curToPrevY = this->curSelectedPosY - this->prevSelectedPosY;
				if (this->canMoveSmooth == false && (curToPrevX * curToPrevX) + (curToPrevY * curToPrevY) <
					this->mouseSelectedPosMinInterval)
				{
					break;
				}
				this->canMoveSmooth = true;

				this->rectX = 0;
				this->rectY = 0;
				this->rectCx = 0;
				this->rectCy = 0;

				float leftToRightSize = abs(this->pSelectedBox->right - this->pSelectedBox->left);
				float topToBottomSize = abs(this->pSelectedBox->bottom - this->pSelectedBox->top);

				this->pSelectedBox->left = point.x - (leftToRightSize / 2);
				this->pSelectedBox->right = point.x + (leftToRightSize / 2);
				this->pSelectedBox->top = point.y - (topToBottomSize / 2);
				this->pSelectedBox->bottom = point.y + (topToBottomSize / 2);

			}
			break;
			default:
				break;
		}
		Invalidate();
	}
}


void CSpriteTool2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (this->isClicked)
	{
		this->isClicked = false;
		this->rectCx = (float)point.x;
		this->rectCy = (float)point.y;

		switch (this->mouseSelectState)
		{
			case MOUSE_SELECT_STATE::DRAW_BOX:
			{
				// 마우스를 조금만 움직였을 경우 상자를 만들지 않는다.
				this->curSelectedPosX = (float)point.x;
				this->curSelectedPosY = (float)point.y;

				float curToPrevX = this->rectCx - this->rectX;
				float curToPrevY = this->rectCy - this->rectY;
				if ((curToPrevX * curToPrevX) + (curToPrevY * curToPrevY) < this->rectMinInterval)
				{
					break;
				}

				ExtractedSprite* slice = new ExtractedSprite(this->rectX, this->rectY, this->rectCx,
					this->rectCy, 0.5f, 0.5f);
				GetDocument()->pResourceManager->extractedSprites.push_back(slice);
			}
			break;
			case MOUSE_SELECT_STATE::SELECT_BOX:
			{
				this->rectX = 0;
				this->rectY = 0;
				this->rectCx = 0;
				this->rectCy = 0;

				// 선택된 상자의 정보를 infoView에 갱신해서 출력
				GetDocument()->pSpriteInfoView->GetSpriteInfo(this->pSelectedBox);
			}
			break;
			default:
				break;
		}
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CSpriteTool2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
	{
		this->isShiftDown = true;
	}

	if (nChar == VK_DELETE)
	{
		// 선택된 slice sprite 지우기
		if (this->pSelectedBox != nullptr)
		{
			auto iter = std::find(GetDocument()->pResourceManager->extractedSprites.begin(),
				GetDocument()->pResourceManager->extractedSprites.end(), this->pSelectedBox);

			if (iter != GetDocument()->pResourceManager->extractedSprites.end())
			{
				GetDocument()->pResourceManager->extractedSprites.erase(iter);
			}
			this->pSelectedBox = nullptr;
			Invalidate();
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSpriteTool2View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
	{
		this->isShiftDown = false;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CSpriteTool2View::OnNewImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LPCTSTR ll = { _T("Image Files(*.bmp;*.png;*.jpg;*.jepg||") };
	CFileDialog dlg(TRUE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ll);
	if (dlg.DoModal() == IDOK)
	{
		GetDocument();
		CString tempFileName;
		dlg.GetPathName();
		tempFileName = dlg.GetPathName();

		LoadBitMapByFilePath(tempFileName);
		// 파일 경로를 알았으니 파일을 불러와야 함.
	}
}

