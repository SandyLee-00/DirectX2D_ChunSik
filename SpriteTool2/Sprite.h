#pragma once


//#include "D2DSprites.h"

#include <afx.h>
#include <vector>

class Sprite : public CObject/*, public D2DSprites*/
{
public:
	int keyColor = 0;
	CD2DBitmap* pD2DBitmap = nullptr;

	Sprite();
	virtual ~Sprite();

	static void ExtractRectsFromSprites(HDC hdc, Sprite* sprite, COLORREF& keyColor, std::vector<CD2DRectU>& outRects);
	void ExtractPixelData();
	static void ExtractRects(Sprite* _sprite, std::vector<D2D1_RECT_F>& _outRects);
private:
	static bool HasConnectedRect(HDC _hdc, COLORREF& _keyColor, const int _X, const int _Y,
		CD2DPointF& _outOrigin, CD2DPointF& _outDimension, int _width, int _height);
	static void FloodFill(HDC _hdc, COLORREF& _keyColor, std::vector<std::vector<bool>>& _maskBitmap,
		int _startX, int _startY);
	static bool HasOverlappingIsland(HDC _hdc, std::vector<std::vector<bool>> _maskBitmap, COLORREF& _keyColor,
		const CD2DPointF& _origin, const CD2DPointF& _dimension, CD2DPointF& _outFill);
	static void GetTightBounds(HDC _hdc, std::vector<std::vector<bool>> _maskBitmap, COLORREF& _keyColor,
		CD2DPointF& _outOrigin, CD2DPointF& _outDimension);

	static bool IsRowEmpty(HDC _hdc, COLORREF& _keyColor, int _X0, int _X1, int _Y);
	static bool IsRowEqual(HDC _hdc, COLORREF& _keyColor, int _X0, int _X1, int _Y);

	static bool IsColumnEmpty(HDC _hdc, COLORREF& _keyColor, int _X, int _Y0, int _Y1);
	static bool IsColumnEqual(HDC _hdc, COLORREF& _keyColor, int _X, int _Y0, int _Y1);

	static void FillRect(std::vector<std::vector<bool>>& _maskBitmap, int _startX, int _startY, int _inWidth,
		int _inHeight);
};

