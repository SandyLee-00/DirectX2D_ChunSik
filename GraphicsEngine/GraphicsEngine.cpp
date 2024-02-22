#include "GraphicsEngine.h"
#include <cassert>

//라이브러리가 없으므로 함수를 못찾았다는 링크 오류가 뜬다
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")	// writefactory
#pragma comment(lib, "windowscodecs.lib") // WIC

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")

HRESULT GraphicsEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	// 2. Create a Direct2D render target.
	if (d2DeviceContext == nullptr)
	{
		CreateDeviceContext();

		RECT rc;
		GetClientRect(hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		hr = pD2DFactory1->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				polyMorphRenderTarget,
				pWICFactory,
				L"D:\\Document\\GA5th2Q_Project\\GA5th2Q_Project\\ChunSik\\4_Resources\\Example\\Example.bmp",
				100,
				0,
				&pBitmap
			);
		}
	}

	return hr;
}

HRESULT GraphicsEngine::CreateDeviceContext()
{
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,                    // 기본 어댑터 사용을 위해 null 지정
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // 디버그 및 Direct2D 호환성 플래그 선택적으로 설정
			featureLevels,              // 이 앱이 지원할 수 있는 기능 레벨 목록
			ARRAYSIZE(featureLevels),   // 가능한 기능 레벨의 수
			D3D11_SDK_VERSION,
			&device,                    // 생성된 Direct3D 장치 반환
			&featureLevel,		    // 생성된 장치의 기능 레벨 반환
			&context                    // 장치의 즉시 컨텍스트 반환
		)
	);
	Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;

	DX::ThrowIfFailed(
		device.As(&dxgiDevice)
	);

	DX::ThrowIfFailed(
		pD2DFactory1->CreateDevice(dxgiDevice.Get(), &pD2DDevice1)
	);

	// Direct2D 장치에 해당하는 장치 컨텍스트 개체를 가져옵니다.
	DX::ThrowIfFailed(
		pD2DDevice1->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&d2DeviceContext
		)
	);

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;										// 자동 크기 조정 사용
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// 가장 일반적인 스왑 체인 포맷
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;								// 멀티샘플링 사용하지 않음
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;									// 더블 버퍼링 사용하여 플립 가능하게 함
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// 모든 앱은 이 SwapEffect를 사용해야 함
	swapChainDesc.Flags = 0;

	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
	DX::ThrowIfFailed(
		dxgiDevice->GetAdapter(&dxgiAdapter)
	);

	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
	DX::ThrowIfFailed(
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
	);

	DXGI_RATIONAL rate{};
	rate.Denominator = 60;
	rate.Numerator = 1;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull{};
	swapChainDescFull.RefreshRate = rate;
	swapChainDescFull.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
	swapChainDescFull.Windowed = true;

	dxgiFactory->CreateSwapChainForHwnd(
		device.Get(),
		hwnd,
		&swapChainDesc,
		&swapChainDescFull, // 전체화면 스왑체인 설정
		nullptr,
		&pSwapChain);

	DX::ThrowIfFailed(
		dxgiDevice->SetMaximumFrameLatency(1)
	);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(
		pSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
	);

	float dpi;
	dpi = (float)GetDpiForWindow(hwnd);

	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			dpi,
			dpi
		);

	Microsoft::WRL::ComPtr<IDXGISurface> dxgiBackBuffer;
	DX::ThrowIfFailed(
		pSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	DX::ThrowIfFailed(
		d2DeviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&pD2DTargetBitmap
		)
	);

	d2DeviceContext->SetTarget(pD2DTargetBitmap);

	if (!d2DeviceContext) return S_FALSE;
	HRESULT hr = d2DeviceContext->CreateCompatibleRenderTarget(
		d2DeviceContext->GetSize(),
		&compatibleRenderTarget
	);

	polyMorphRenderTarget = d2DeviceContext;

	return S_OK;
}

bool GraphicsEngine::AnimationTimer(ULONGLONG* _time, ULONGLONG _timeLength, bool _sorMS)
{
	*_time += deltaTime;
	if (_sorMS)
	{
		if ((*_time / 1000) >= _timeLength)
		{
			*_time -= (1000 * _timeLength);
			return true;
		}
	}
	else
	{
		if (*_time >= _timeLength)
		{
			*_time -= _timeLength;
			if (*_time > _timeLength * 2)
			{
				*_time = 0;
			}
			return true;
		}
	}
	return false;
}
 
void GraphicsEngine::EffectBufferB()
{
	polyMorphRenderTarget = compatibleRenderTarget;

	compatibleRenderTarget->BeginDraw();
	compatibleRenderTarget->Clear(D2D1::ColorF::ColorF(D2D1::ColorF::ColorF::White));
	compatibleRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void GraphicsEngine::EffectBufferE()
{
	compatibleRenderTarget->EndDraw();

	ID2D1Bitmap* pTemp = nullptr;
	compatibleRenderTarget->GetBitmap(&pTemp);
	polyMorphRenderTarget = d2DeviceContext;

	for(auto& eff : this->efffects) 
	{
		effect->SetInput(0, spriteSheets[eff.second.sheetNumEff]);

		effect->SetValue(D2D1_OPACITY_PROP_OPACITY, eff.second.opercity);
		effect->GetOutput(&pImage);
		d2DeviceContext->DrawImage(pImage, D2D1::Point2F(eff.second.x, eff.second.y));
	}

	//d2DeviceContext->DrawImage(pImage);

	///내가 할 작업은 따로 있지
	//CreateEffects();
}

void GraphicsEngine::SetEffect(const std::string& _name, float _op,int _sheetEff, int _x, int _y)
{
	this->efffects[_name] = EffectInfo{_op, _sheetEff, (float)_x, (float)_y} ;
}

void GraphicsEngine::SetIsEffOn()
{
	isEff = true;
}

void GraphicsEngine::SetIsEffOff()
{
	isEff = false;
}

GraphicsEngine::GraphicsEngine() : pD2DFactory1(nullptr), spriteCount(0), spriteSheetCount(0), isEff(false)
{
}

GraphicsEngine::~GraphicsEngine()
{
	Finalize();
}

void GraphicsEngine::Initialize(HWND hWnd)
{
	hwnd = hWnd;

	HRESULT hr = S_OK;

	static const WCHAR msc_fontName[] = L"던파 비트비트체 TTF";
	fontSize = 36;
	//static const FLOAT msc_fontSize = 12;

	// 1. Direct2D Factory를 만든다.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory1);

	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&pWICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"", //locale
			&pTextFormat
		);
	}
	//폰트 불러오기 
	//const std::wstring& path = L"DNFBitBitTTF.ttf";
	//AddFontResourceW(path.c_str());
	//::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);

	//hr = pDWriteFactory->CreateTextFormat(
	//	L"던파비트비트체",
	//	NULL,
	//	DWRITE_FONT_WEIGHT_NORMAL,
	//	DWRITE_FONT_STYLE_NORMAL,
	//	DWRITE_FONT_STRETCH_NORMAL,
	//	36,
	//	L"", //locale
	//	&pTextFormat
	//);

	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}

	isDDResReady = CreateDeviceResources();

	previousTime = currentTime = GetTickCount64();

	polyMorphRenderTarget->QueryInterface(&d2DeviceContext);

	d2DeviceContext->CreateEffect(CLSID_D2D1Opacity, &effect);
}

void GraphicsEngine::BDraw()
{
	isDDResReady = CreateDeviceResources();

	if (SUCCEEDED(isDDResReady) && !(pRenderTarget->CheckWindowState() && D2D1_WINDOW_STATE_OCCLUDED))
	{
		// Retrieve the size of the render target.
		D2D1_SIZE_F renderTargetSize = d2DeviceContext->GetSize();

		d2DeviceContext->BeginDraw();

		d2DeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

		d2DeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
	}


}

void GraphicsEngine::EDraw()
{
	if (isEff)
	{
		EffectBufferB();
		EffectBufferE();
	}


	if (SUCCEEDED(isDDResReady) && !(pRenderTarget->CheckWindowState() && D2D1_WINDOW_STATE_OCCLUDED))
	{
		HRESULT hr = d2DeviceContext->EndDraw();

		///이걸 해줬어야했다. 안해줘서 안그려졌다.
		DXGI_PRESENT_PARAMETERS parameters{};
		parameters.DirtyRectsCount = 0;			// 0이면 전체 프레임 업데이트
		parameters.pDirtyRects = nullptr;		// DirtyRectsCount가 0이면 NULL로 설정 가능
		parameters.pScrollRect = nullptr;		// NULL이면 콘텐츠가 이전 프레임에서 스크롤되지 않음
		parameters.pScrollOffset = nullptr;		// NULL이면 오프셋 없음

		DX::ThrowIfFailed(
			pSwapChain->Present1(1, 0, &parameters)
		);
	}
}

void GraphicsEngine::Finalize()
{
	SafeRelease(&pDirect2DFactory);
	SafeRelease(&pRenderTarget);
}

void GraphicsEngine::ColorSet(D2D1::ColorF::Enum e)
{
	if (this->brushs.find(e) != this->brushs.end())
	{
		pBrushColor = this->brushs.find(e)->second;
	}
	else
	{
		polyMorphRenderTarget->CreateSolidColorBrush(D2D1::ColorF(e), &pBrushColor);
		this->brushs.insert({ e, pBrushColor });
	}
}

// left, top, right, bottom
void GraphicsEngine::DrawRectangle(int _x, int _y, int _x1, int _y1)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	polyMorphRenderTarget->FillRectangle(D2D1::RectF((FLOAT)_x, (FLOAT)_y, (FLOAT)_x1, (FLOAT)_y1), pBrushColor);
}

// left, top, right, bottom
void GraphicsEngine::DrawRectangle(float _x, float _y, float _x1, float _y1)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	polyMorphRenderTarget->FillRectangle(D2D1::RectF(_x, _y, _x1, _y1), pBrushColor);
}
// centerX, centerY, radiusX, radiusY
void GraphicsEngine::DrawCircle(int _x, int _y, int _x1, int _y1)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	polyMorphRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F((FLOAT)_x, (FLOAT)_y), (FLOAT)_x1, (FLOAT)_y1), pBrushColor);
}

// centerX, centerY, radiusX, radiusY
void GraphicsEngine::DrawCircle(float _x, float _y, float _x1, float _y1)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	polyMorphRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(_x, _y), _x1, _y1), pBrushColor);
}

// left, top, right, bottom
void GraphicsEngine::DrawEmptyRect(int _x, int _y, int _x1, int _y1)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	polyMorphRenderTarget->DrawRectangle(D2D1::RectF((FLOAT)_x, (FLOAT)_y, (FLOAT)_x1, (FLOAT)_y1), pBrushColor);
}

// left, top, right, bottom
void GraphicsEngine::DrawEmptyRect(float _x, float _y, float _x1, float _y1)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	polyMorphRenderTarget->DrawRectangle(D2D1::RectF(_x, _y, _x1, _y1), pBrushColor);

}

bool GraphicsEngine::DrawTextCC(int _x, int _y, const char* _pch, ...)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, _pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(_pch, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, _pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		polyMorphRenderTarget->DrawText(unicodestr, wcslen(unicodestr), pTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)_x, (float)_y, (float)(_x + 500), (float)(_y + 40)),
			pBrushColor);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

bool GraphicsEngine::CenterDrawTextCC(int _x, int _y, const char* _pch, ...)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, _pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(_pch, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, _pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		polyMorphRenderTarget->DrawText(unicodestr, wcslen(unicodestr), pTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)_x, (float)_y, (float)(_x + 500), (float)(_y + 40)),
			pBrushColor, D2D1_DRAW_TEXT_OPTIONS_CLIP, DWRITE_MEASURING_MODE_NATURAL);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

bool GraphicsEngine::DrawString(int _x, int _y, std::string _pch, ...)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, _pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(_pch.c_str(), ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, _pch.c_str(), ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		polyMorphRenderTarget->DrawText(unicodestr, wcslen(unicodestr), pTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)_x, (float)_y, (float)(_x + 700), (float)(_y + 70)),
			pBrushColor);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

bool GraphicsEngine::CenterDrawString(int _x, int _y, std::string _pch, ...)
{
	if (pBrushColor == nullptr)
	{
		assert(pBrushColor != nullptr && "pBurshColor is a null pointer!");
	}
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, _pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(_pch.c_str(), ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, _pch.c_str(), ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		polyMorphRenderTarget->DrawText(unicodestr, wcslen(unicodestr), pTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)_x, (float)_y, (float)(_x + 500), (float)(_y + 40)),
			pBrushColor, D2D1_DRAW_TEXT_OPTIONS_CLIP, DWRITE_MEASURING_MODE_NATURAL);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

void GraphicsEngine::DrawSprite(std::string _name, int _index, float _dstX, float _dstY, int _width, int _height)
{
	D2DSprites _newD2DSprite = D2DSprites();
	DrawObj object = DrawObj();
	//object->sprites.pushback(_newD2DSprite);
	object.spriteMap.insert(std::make_pair(_name, _newD2DSprite));

	//정신사나울 수 있다. 하지만 난 이게 편할거같다.
	object.spriteMap[_name].sheetIndex = 0;
	object.spriteMap[_name].index = 0;

	object.spriteMap[_name].oriX = (int)_dstX;
	object.spriteMap[_name].oriY = (int)_dstY;
	object.spriteMap[_name].width = _width;
	object.spriteMap[_name].height = _height;

	///결정타
	_newD2DSprite.sheetIndex = _index;
	ID2D1Bitmap* _sheet = spriteSheets[_newD2DSprite.sheetIndex];	// 인덱스 접근 시 실패체크도 해야 함
	if (_sheet != NULL)
	{
		D2D1_SIZE_F size = _sheet->GetSize();

		polyMorphRenderTarget->DrawBitmap(_sheet,
			D2D1::RectF((float)object.spriteMap[_name].oriX, (float)object.spriteMap[_name].oriY, (float)(object.spriteMap[_name].oriX + object.spriteMap[_name].width), (float)(object.spriteMap[_name].oriY + object.spriteMap[_name].height)),
			1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(0, 0, size.width, size.height)
		);

	}
}

void GraphicsEngine::DrawSpriteAnimation(std::string _name, int _index, int _motions, int _nowMotion, int _sprite, int _dstX, int _dstY, int _width, int _height, int _prame)
{
	D2DSprites _newD2DSprite = D2DSprites();
	DrawObj object = DrawObj();

	object.motionNum = _motions;

	// 모션 갯수만큼 돌면서, 각 모션당 스프라이트의 갯수를 얻는다.
	for (int i = 0; i <= object.motionNum; i++)
	{
		// 모션을 생성한다.
		DrawMotions _newMotion = DrawMotions();
		_newMotion.Index = i;
		_newMotion.SpriteNum = _sprite;

		object.Motions.push_back(_newMotion);
	}

	for (int i = 0; i <= object.motionNum; i++)
	{
		for (int j = 0; j <= object.Motions[i].SpriteNum; j++)
		{
			// 일단 모두 0으로 생성만 모두 하자.
			D2DSprites _newD2DSprite = D2DSprites();
			object.Motions[i].motionSprites.push_back(_newD2DSprite);
		}
	}

	///이걸로는 변하는 스프라이트 갯수를 잡을 수 없어..
	//int _spriteWidthTemp[4] = { _width, _width, _width, _width };
	//int _spriteHeightTemp[4] = { _height, _height, _height, _height };

	int* spriteWidthTemp = new int[_sprite];
	int* spriteHeightTemp = new int[_sprite];

	for (int i = 0; i < _sprite; i++)
	{
		spriteWidthTemp[i] = _width;
	}

	for (int i = 0; i < _sprite; i++)
	{
		spriteHeightTemp[i] = _height;
	}

	int _oriPosX = _dstX;
	int _oriPosY = _dstY;

	for (int j = 0; j <= object.motionNum; j++)
	{
		for (int i = 0; i <= object.Motions[j].SpriteNum; i++)
		{
			// D2DSprite (PickPos)에만 있는 내용
			object.Motions[j].motionSprites[i].sheetIndex = 0;
			object.Motions[j].motionSprites[i].oriX = _oriPosX;	// 원본 스프라이트 시트로부터의 위치이며, 이번에는 각자 가지고 있어야 한다.
			object.Motions[j].motionSprites[i].oriY = _oriPosY;

			// DRSprite에 있는 내용
			//야다야다
			//_object->Motions[j]->motionSprites[i]->spriteType = D2DSprite::SpriteType::ePickPos;
			object.Motions[j].motionSprites[i].index = i;
			object.Motions[j].motionSprites[i].width = spriteWidthTemp[j];	// Bitmap을 기준으로 만들어줬었으나, 이번에는 각자 가지고 있어야 한다.
			object.Motions[j].motionSprites[i].height = spriteHeightTemp[j];
			object.Motions[j].motionSprites[i].keycolor = RGB(255, 0, 255);	// Direct2D에서는 쓰지 않는다.

			_oriPosX += spriteWidthTemp[j];
		}

		// 맨 처음 줄로 되돌아가므로
		_oriPosX = _dstX;
		_oriPosY += spriteHeightTemp[j];
	}

	previousTime = currentTime;
	currentTime = GetTickCount64();
	deltaTime = currentTime - previousTime;
	///결정타
	_newD2DSprite.sheetIndex = _index;
	ID2D1Bitmap* _sheet = spriteSheets[_newD2DSprite.sheetIndex];	// 인덱스 접근 시 실패체크도 해야 함
	if (_sheet != NULL)
	{
		if (AnimationTimer(&fixedTime, _prame, false))
		{
			_nowSprite++;
			if (_nowSprite >= object.Motions[_nowMotion].SpriteNum)
			{
				_nowSprite = 0;
			}


		}
		polyMorphRenderTarget->DrawBitmap(_sheet,
			D2D1::RectF((float)_dstX,
				(float)_dstY,
				(float)(_dstX
					+ object.Motions[_nowMotion].motionSprites[_nowSprite].width),
				(float)(_dstY
					+ object.Motions[_nowMotion].motionSprites[_nowSprite].height)),
			1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((float)object.Motions[_nowMotion].motionSprites[_nowSprite].oriX,
				(float)object.Motions[_nowMotion].motionSprites[_nowSprite].oriY,
				(float)(object.Motions[_nowMotion].motionSprites[_nowSprite].oriX
					+ object.Motions[_nowMotion].motionSprites[_nowSprite].width),
				(float)(object.Motions[_nowMotion].motionSprites[_nowSprite].oriY
					+ object.Motions[_nowMotion].motionSprites[_nowSprite].height))
		);
	}

	delete[] spriteWidthTemp;
	delete[] spriteHeightTemp;
}

void GraphicsEngine::DrawSpriteAni(std::string _name, D2DSprites _newD2DSprite, int _index, float _dstX, float _dstY)
{
	// D2DSprites _newD2DSprite = D2DSprites();
	DrawObj object = DrawObj();
	// object.sprites.pushback(_newD2DSprite);
	//object.spriteMap.insert(std::make_pair(_name, _newD2DSprite));

	////정신사나울 수 있다. 하지만 난 이게 편할거같다.
	//object.spriteMap[_name].sheetIndex = 0;
	//object.spriteMap[_name].index = 0;

	//object.spriteMap[_name].oriX = _dstX;
	//object.spriteMap[_name].oriY = _dstY;

	///결정타
	_newD2DSprite.sheetIndex = _index;
	ID2D1Bitmap* _sheet = spriteSheets[_newD2DSprite.sheetIndex];	// 인덱스 접근 시 실패체크도 해야 함
	if (_sheet != NULL)
	{
		D2D1_SIZE_F size = _sheet->GetSize();

		polyMorphRenderTarget->DrawBitmap(_sheet,
			D2D1::RectF((float)_dstX, (float)_dstY, (float)(_dstX + _newD2DSprite.width), (float)(_dstY + _newD2DSprite.height)),
			1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((float)_newD2DSprite.oriX, (float)_newD2DSprite.oriY, (float)(_newD2DSprite.oriX + _newD2DSprite.width), (float)(_newD2DSprite.oriY + _newD2DSprite.height))
		);

	}
}

int GraphicsEngine::LoadSpriteSheet(const char* _filePath)
{
	size_t newsize = strlen(_filePath) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, _filePath, _TRUNCATE);
	wchar_t* _wcstring = wcstring;

	int _result = LoadSpriteSheet(_wcstring);
	delete[] _wcstring;
	return _result;
}

int GraphicsEngine::LoadSpriteSheet(const wchar_t* _filePath)
{
	HRESULT hr;
	ID2D1Bitmap* pNewBitmap;

	// Create a bitmap by loading it from a file.
	hr = LoadBitmapFromFile(
		polyMorphRenderTarget,
		pWICFactory,
		_filePath,
		0,
		0,
		&pNewBitmap
	);

	if (SUCCEEDED(hr))
	{
		spriteSheets.push_back(pNewBitmap);
		spriteSheetCount++;

		return (spriteSheetCount - 1);
	}

	return -1;
}

void GraphicsEngine::CreateEffects()
{
	polyMorphRenderTarget->QueryInterface(&d2DeviceContext);

	d2DeviceContext->CreateEffect(CLSID_D2D1Brightness, &exampleEff);
	exampleEff->SetInput(0, spriteSheets[0]);

	exampleEff->SetValue(D2D1_BRIGHTNESS_PROP_BLACK_POINT, D2D1::Vector2F(0.0f, 0.0f));

	exampleEff->GetOutput(&pImage);

	ID2D1Bitmap* _sheet = spriteSheets[0];
	if (_sheet != NULL)
	{
		D2D1_SIZE_U size2 = { (UINT32)(_sheet)->GetSize().width, (UINT32)(_sheet)->GetSize().height };
		_sheet = ConvertImageToBitmap(pImage, size2);

		spriteSheets[0] = _sheet;
	}
}

ID2D1Bitmap* GraphicsEngine::ConvertImageToBitmap(ID2D1Image* pImg, D2D1_SIZE_U size)
{
	ID2D1Image* oldTarget = NULL;
	ID2D1Bitmap1* targetBitmap = NULL;

	// "D2D1_BITMAP_OPTIONS_TARGET" 모드로 적절한 비트맵을 생성.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	d2DeviceContext->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);

	// 현재 타겟을 저장 해둔다. 그리고 새로 그릴 ID2D1Bitmap 으로 바꿈.
	d2DeviceContext->GetTarget(&oldTarget);
	d2DeviceContext->SetTarget(targetBitmap);
	// DC 에 Image를 그림.
	d2DeviceContext->BeginDraw();
	d2DeviceContext->DrawImage(pImg);
	d2DeviceContext->EndDraw();
	// 비트맵에 해당되는 이미지가 그려졌으므로 해당 비트맵을 리턴한다.
	d2DeviceContext->SetTarget(oldTarget);

	oldTarget->Release();

	return targetBitmap;
}

void GraphicsEngine::DrawCaret(float x, float y)
{
	this->polyMorphRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	polyMorphRenderTarget->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x, y), this->pBrushColor);
}

float GraphicsEngine::fontSize = 12.f;

void GraphicsEngine::ChangeFontSize(float _size)
{
	fontSize = _size;
	this->pTextFormat->Release();
	this->pDWriteFactory->CreateTextFormat(
		L"던파 비트비트체 TTF",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"", //locale
		&pTextFormat
	);
}

HRESULT GraphicsEngine::LoadBitmapFromFile(ID2D1RenderTarget* _pRenderTarget,
	IWICImagingFactory* _pIWICFactory, PCWSTR _uri, UINT _destinationWidth,
	UINT _destinationHeight, ID2D1Bitmap** _ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = _pIWICFactory->CreateDecoderFromFilename(
		_uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = _pIWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (_destinationWidth != 0 || _destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (_destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationHeight) / static_cast<FLOAT>(originalHeight);
					_destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (_destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationWidth) / static_cast<FLOAT>(originalWidth);
					_destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = _pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						_destinationWidth,
						_destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = polyMorphRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			_ppBitmap
		);
	}

	return hr;
}