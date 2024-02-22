///그래픽스 엔진 by 김예리나
///7.26일 시작~
#pragma once
#include <d2d1.h>
#include <d2d1_1.h>
#include <wincodec.h>
#include <Windows.h>
#include <map>
#include <vector>
#include <dwrite.h>
#include <filesystem>

#include <d3d11.h>		
#include <dxgi1_2.h>	
#include "d2d1effects_2.h"

#include <wrl.h>

#include "D2DSprites.h"
#include "DrawObj.h"
#include "DXd2dtk.h"


struct EffectInfo
{
	float opercity;
	int sheetNumEff;
	float x;
	float y;
};

class GraphicsEngine
{
private:
	HWND hwnd{}; //도화지

	ID2D1Factory* pDirect2DFactory = nullptr; //d2d객체를 생성,관리하는 공장
	ID2D1HwndRenderTarget* pRenderTarget = nullptr; //프로그램이 그릴 위치
	HRESULT isDDResReady{};		// 디바이스 종속적인 자원들이 준비되었는지 체크
	ID2D1Bitmap* pBitmap = nullptr;	// 비트맵
	ID2D1SolidColorBrush* pBrushColor = nullptr; //브러쉬
	std::vector<ID2D1Bitmap*> spriteSheets;	// 스프라이트 시트
	IWICImagingFactory* pWICFactory = nullptr; //
	int spriteCount = 0;			// 스프라이트의 갯수 (인덱스는 0부터)
	std::vector<D2DSprites*> spriteInfos;
	int spriteSheetCount = 0;		// 스프라이트 시트의 갯수 (인덱스는 0부터) 그니까 스프라이트 안에 쪼개지는 그림
	IDWriteFactory* pDWriteFactory = nullptr;
	IDWriteTextFormat* pTextFormat = nullptr;
	IDWriteFontCollection* pFontCollection = nullptr; //커스텀 폰트

	ULONGLONG previousTime = 0; // 이전 프레임 시간
	ULONGLONG currentTime = 0; // 현재
	ULONGLONG deltaTime = 0; //프레임과 프레임의 시간간격
	__int64 countsPerSec = 0;
	ULONGLONG fixedTime = 0;
	int _nowSprite = 0;

	///=------------------------------------------------------------------------------------------------------------------------
	ID2D1Factory1* pD2DFactory1 = nullptr;

	ID2D1DeviceContext* d2DeviceContext = nullptr;
	D3D_FEATURE_LEVEL featureLevel; //featureLevel{}
	ID2D1Device* pD2DDevice1 = nullptr;					
	IDXGISwapChain1* pSwapChain = nullptr;
	ID2D1Bitmap1* pD2DTargetBitmap = nullptr;
	float dpi = 0.f;

	ID2D1Effect* exampleEff = nullptr;
	ID2D1Image* pImage = nullptr;

	HRESULT CreateDeviceResources();
	HRESULT CreateDeviceContext();

	bool AnimationTimer(ULONGLONG* _pTime, ULONGLONG _timeLength, bool _sorMS);

	//파일을 불러옵니다.
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* _pRenderTarget, IWICImagingFactory* _pIWICFactory, PCWSTR _uri,
		UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _ppBitmap
	);

	std::map<D2D1::ColorF::Enum, ID2D1SolidColorBrush*> brushs;
	
	///버퍼를 위한 변수들. 일단 따라치고보자 . 문제가 생기면 리버트
	/// Buffer
	ID2D1Bitmap1* originalBuffer;
	ID2D1BitmapRenderTarget* compatibleRenderTarget;
	ID2D1RenderTarget* polyMorphRenderTarget;
	Microsoft::WRL::ComPtr<ID2D1Effect> effect;
	float opercity;
	int sheetNumEff;
	float effX;
	float effY;
	bool isEff;

	std::map<std::string, EffectInfo> efffects;

	void EffectBufferB();
	void EffectBufferE();

public:

	GraphicsEngine();
	~GraphicsEngine();

	///그리는 루프 담당하는 함수
	void Initialize(HWND _hWnd);
	void BDraw();
	void EDraw();
	void Finalize();

	///데려가서 그려주는 함수
	//색깔을 넣어주면 돼요.
	void ColorSet(D2D1::ColorF::Enum e);

	///저는 Z 모양으로 꼭짓점을 받을겁니다.
	//int로 꼭짓점을 받는 꽉찬 사각형
	void DrawRectangle(int _x, int _y, int _x1, int _y1);
	//float로 꼭짓점을 받는 꽉찬 사각형
	void DrawRectangle(float _x, float _y, float _x1, float _y1);
	//int로 중심과 지름을 받는 원
	void DrawCircle(int _x, int _y, int _x1, int _y1);
	//float로 중심과 지름을 받는 원
	void DrawCircle(float _x, float _y, float _x1, float _y1);
	//int로 꼭짓점을 받는 빈 사각형
	void DrawEmptyRect(int _x, int _y, int _x1, int _y1);
	//float로 꼭짓점을 받는 빈 사각형
	void DrawEmptyRect(float _x, float _y, float _x1, float _y1);

	///글자 출력
	//const char* 형으로 받는 글씨 쓰는 함수
	bool DrawTextCC(int _x, int _y, const char* _pch, ...);
	bool CenterDrawTextCC(int _x, int _y, const char* _pch, ...);
	//std::string 형으로 받는 글씨 쓰는 함수
	bool DrawString(int _x, int _y, std::string _pch, ...);
	bool CenterDrawString(int _x, int _y, std::string _pch, ...);

	///여기서부턴 비트맵 그리고 돌리기
	//그림 하나만 그리는 함수. 
	//이름, 그림의 인덱스, x좌표, y 좌표, 길이, 넓이를 매개변수로 받습니다.
	void DrawSprite(std::string _name,int _index, float _dstX, float _dstY,int _width, int _height);
	//그림으로 애니메이션을 그리는 함수
	//이름, 그림의 인덱스, 총합 모션, 현재 모션,재생할 모션의 스프라이트, x,y좌표, 길이, 넓이, 애니메이션의 프레임을 매개변수로 받습니다.
	void DrawSpriteAnimation(std::string _name, int _index,  int _motions, int _nowMotion, int _sprite, int _dstX, int _dstY, int _width, int _height,int _prame);
	//굳이 알필요없습니다. 차라리 Animation::SetSpriteRes을 보세요.
	void DrawSpriteAni(std::string _name, D2DSprites _newD2DSprite, int _index, float _dstX, float _dstY );
	//그림의 위치를 가져옵니다.
	int LoadSpriteSheet(const char* _filePath);
	//그림의 위치를 가져오지만...뭔가가 더있긴하다 연계콤보같은거라 const char*만 일단 써도 괜찮다.
	int LoadSpriteSheet(const wchar_t* _filePath);

	///여기서부터는 이펙트다. 눌러버리자
	virtual void CreateEffects();
	ID2D1Bitmap* ConvertImageToBitmap(ID2D1Image* pImg, D2D1_SIZE_U size);
	void SetEffect(const std::string& _name, float _op, int _sheetEff,int _x,int _y);
	void SetIsEffOn();
	void SetIsEffOff();

	// 김정우
	// 캐럿을 그리는 함수
	void DrawCaret(float x, float y);

	static float fontSize;
	void ChangeFontSize(float _size);
};


// 인터페이스의 안전한 메모리 해제
template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}