///�׷��Ƚ� ���� by �迹����
///7.26�� ����~
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
	HWND hwnd{}; //��ȭ��

	ID2D1Factory* pDirect2DFactory = nullptr; //d2d��ü�� ����,�����ϴ� ����
	ID2D1HwndRenderTarget* pRenderTarget = nullptr; //���α׷��� �׸� ��ġ
	HRESULT isDDResReady{};		// ����̽� �������� �ڿ����� �غ�Ǿ����� üũ
	ID2D1Bitmap* pBitmap = nullptr;	// ��Ʈ��
	ID2D1SolidColorBrush* pBrushColor = nullptr; //�귯��
	std::vector<ID2D1Bitmap*> spriteSheets;	// ��������Ʈ ��Ʈ
	IWICImagingFactory* pWICFactory = nullptr; //
	int spriteCount = 0;			// ��������Ʈ�� ���� (�ε����� 0����)
	std::vector<D2DSprites*> spriteInfos;
	int spriteSheetCount = 0;		// ��������Ʈ ��Ʈ�� ���� (�ε����� 0����) �״ϱ� ��������Ʈ �ȿ� �ɰ����� �׸�
	IDWriteFactory* pDWriteFactory = nullptr;
	IDWriteTextFormat* pTextFormat = nullptr;
	IDWriteFontCollection* pFontCollection = nullptr; //Ŀ���� ��Ʈ

	ULONGLONG previousTime = 0; // ���� ������ �ð�
	ULONGLONG currentTime = 0; // ����
	ULONGLONG deltaTime = 0; //�����Ӱ� �������� �ð�����
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

	//������ �ҷ��ɴϴ�.
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* _pRenderTarget, IWICImagingFactory* _pIWICFactory, PCWSTR _uri,
		UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _ppBitmap
	);

	std::map<D2D1::ColorF::Enum, ID2D1SolidColorBrush*> brushs;
	
	///���۸� ���� ������. �ϴ� ����ġ���� . ������ ����� ����Ʈ
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

	///�׸��� ���� ����ϴ� �Լ�
	void Initialize(HWND _hWnd);
	void BDraw();
	void EDraw();
	void Finalize();

	///�������� �׷��ִ� �Լ�
	//������ �־��ָ� �ſ�.
	void ColorSet(D2D1::ColorF::Enum e);

	///���� Z ������� �������� �����̴ϴ�.
	//int�� �������� �޴� ���� �簢��
	void DrawRectangle(int _x, int _y, int _x1, int _y1);
	//float�� �������� �޴� ���� �簢��
	void DrawRectangle(float _x, float _y, float _x1, float _y1);
	//int�� �߽ɰ� ������ �޴� ��
	void DrawCircle(int _x, int _y, int _x1, int _y1);
	//float�� �߽ɰ� ������ �޴� ��
	void DrawCircle(float _x, float _y, float _x1, float _y1);
	//int�� �������� �޴� �� �簢��
	void DrawEmptyRect(int _x, int _y, int _x1, int _y1);
	//float�� �������� �޴� �� �簢��
	void DrawEmptyRect(float _x, float _y, float _x1, float _y1);

	///���� ���
	//const char* ������ �޴� �۾� ���� �Լ�
	bool DrawTextCC(int _x, int _y, const char* _pch, ...);
	bool CenterDrawTextCC(int _x, int _y, const char* _pch, ...);
	//std::string ������ �޴� �۾� ���� �Լ�
	bool DrawString(int _x, int _y, std::string _pch, ...);
	bool CenterDrawString(int _x, int _y, std::string _pch, ...);

	///���⼭���� ��Ʈ�� �׸��� ������
	//�׸� �ϳ��� �׸��� �Լ�. 
	//�̸�, �׸��� �ε���, x��ǥ, y ��ǥ, ����, ���̸� �Ű������� �޽��ϴ�.
	void DrawSprite(std::string _name,int _index, float _dstX, float _dstY,int _width, int _height);
	//�׸����� �ִϸ��̼��� �׸��� �Լ�
	//�̸�, �׸��� �ε���, ���� ���, ���� ���,����� ����� ��������Ʈ, x,y��ǥ, ����, ����, �ִϸ��̼��� �������� �Ű������� �޽��ϴ�.
	void DrawSpriteAnimation(std::string _name, int _index,  int _motions, int _nowMotion, int _sprite, int _dstX, int _dstY, int _width, int _height,int _prame);
	//���� ���ʿ�����ϴ�. ���� Animation::SetSpriteRes�� ������.
	void DrawSpriteAni(std::string _name, D2DSprites _newD2DSprite, int _index, float _dstX, float _dstY );
	//�׸��� ��ġ�� �����ɴϴ�.
	int LoadSpriteSheet(const char* _filePath);
	//�׸��� ��ġ�� ����������...������ ���ֱ��ϴ� �����޺������Ŷ� const char*�� �ϴ� �ᵵ ������.
	int LoadSpriteSheet(const wchar_t* _filePath);

	///���⼭���ʹ� ����Ʈ��. ����������
	virtual void CreateEffects();
	ID2D1Bitmap* ConvertImageToBitmap(ID2D1Image* pImg, D2D1_SIZE_U size);
	void SetEffect(const std::string& _name, float _op, int _sheetEff,int _x,int _y);
	void SetIsEffOn();
	void SetIsEffOff();

	// ������
	// ĳ���� �׸��� �Լ�
	void DrawCaret(float x, float y);

	static float fontSize;
	void ChangeFontSize(float _size);
};


// �������̽��� ������ �޸� ����
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