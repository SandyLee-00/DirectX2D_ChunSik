#include "pch.h"
#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void Sprite::ExtractRectsFromSprites(HDC hdc, Sprite* sprite, COLORREF& keyColor, std::vector<CD2DRectU>& outRects)
{

}

void Sprite::ExtractPixelData()
{
	// 비트맵 크기 및 픽셀 형식 가져오기
	D2D1_SIZE_U size = this->pD2DBitmap->GetPixelSize();
	D2D1_BITMAP_PROPERTIES properties{};

	this->pD2DBitmap->Get()->GetDpi(&properties.dpiX, &properties.dpiY);

	// 비트맵 데이터를 저장할 메모리 버퍼 생성
	BYTE* pBuffer = new BYTE[size.width * size.height * 4]; // 4 bytes per pixel (assuming 32-bit RGBA format)


	// ID2D1Bitmap에서 메모리 버퍼로 데이터 복사
	D2D1_RECT_U rect = D2D1::RectU(0, 0, size.width, size.height);
	HRESULT hr = this->pD2DBitmap->Get()->CopyFromMemory(&rect, pBuffer, size.width * 4);

	if (SUCCEEDED(hr))
	{
		// 픽셀 데이터 읽기
		for (UINT y = 0; y < size.height; y++)
		{
			for (UINT x = 0; x < size.width; x++)
			{
				UINT offset = (y * size.width + x) * 4; // 4 bytes per pixel (RGBA)
				BYTE red = pBuffer[offset];
				BYTE green = pBuffer[offset + 1];
				BYTE blue = pBuffer[offset + 2];
				BYTE alpha = pBuffer[offset + 3];
			}
		}
	}

	// 메모리 누수 방지를 위해 메모리 해제
	delete[] pBuffer;
}

void Sprite::ExtractRects(Sprite* _sprite, std::vector<D2D1_RECT_F>& _outRects)
{

}

bool Sprite::HasConnectedRect(HDC _hdc, COLORREF& _keyColor, const int _X, const int _Y, CD2DPointF& _outOrigin,
	CD2DPointF& _outDimension, int _width, int _height)
{
	if (GetPixel(_hdc, _X, _Y) == _keyColor)
	{
		// selected an empty pixel
		_outOrigin.x = 0;
		_outOrigin.y = 0;
		_outDimension.x = 0;
		_outDimension.y = 0;

		return false;
	}

	int numPasses = 0;
	int maxPasses = 40;
	CD2DPointF origin(0, 0);
	CD2DPointF dimension(0, 0);
	CD2DPointF fillPoint((float)_X, (float)_Y);

	std::vector<std::vector<bool>> maskBitmap(_height, std::vector<bool>(_width, false));
	// TODO : temp while true
	do
	{
		//FloodFill
		FloodFill(_hdc, _keyColor, maskBitmap, _X, _Y);
		GetTightBounds(_hdc, maskBitmap, _keyColor, origin, dimension);
	} while (numPasses++ < maxPasses && HasOverlappingIsland(_hdc, maskBitmap, _keyColor, origin, dimension,
		fillPoint));

	_outOrigin = origin;
	_outDimension = dimension;

	return true;
}

void Sprite::FloodFill(HDC _hdc, COLORREF& _keyColor, std::vector<std::vector<bool>>& _maskBitmap, int _startX,
	int _startY)
{
	std::vector<CD2DPointF> queuedPoints;
	queuedPoints.reserve(_maskBitmap.size());

	queuedPoints.push_back(CD2DPointF((float)_startX, (float)_startY));
	while (queuedPoints.size() > 0)
	{
		CD2DPointF point = queuedPoints.back();
		queuedPoints.pop_back();
		if (point.y < 0 || point.x < 0 || point.y > _maskBitmap.size() - 1 || point.x > _maskBitmap[0].size() - 1)
		{
			continue;
		}
		if (_maskBitmap[(int)point.y][(int)point.x] == false && GetPixel(_hdc, (int)point.x, (int)point.y) != 
			_keyColor)
		{
			_maskBitmap[(int)point.y][(int)point.x] = true;
			if (point.x > 0)
			{
				queuedPoints.push_back(CD2DPointF(point.x - 1, point.y));
			}
			if (point.x < _maskBitmap.size() - 1)
			{
				queuedPoints.push_back(CD2DPointF(point.x + 1, point.y));
			}
			if (point.y > 0)
			{
				queuedPoints.push_back(CD2DPointF(point.x, point.y - 1));
			}
			if (point.y < _maskBitmap[0].size() - 1)
			{
				queuedPoints.push_back(CD2DPointF(point.x, point.y + 1));
			}
		}
	}
}

bool Sprite::HasOverlappingIsland(HDC _hdc, std::vector<std::vector<bool>> _maskBitmap, COLORREF& _keyColor,
	const CD2DPointF& _origin, const CD2DPointF& _dimension, CD2DPointF& _outFill)
{
	// 방문하지 않은 영역이며, 유효한 색상이라면),
	// OutFill 변수에 해당 위치를 저장하고, true를 반환. 즉, 겹치는 도형이 있다는 것을 의미
	// 사각형의 네 변을 모두 순회한 뒤에도 겹치는 도형이 발견되지 않았다면, false를 반환

	_outFill.x = 0;
	_outFill.y = 0;
	const int X0 = (int)_origin.x;
	const int Y0 = (int)_origin.y;
	const int X1 = (int)_origin.x + (int)_dimension.x - 1;
	const int Y1 = (int)_origin.y + (int)_dimension.y - 1;

	for (int X = X0; X <= X1; ++X)
	{
		if (_maskBitmap[Y0][X] == false && GetPixel(_hdc, X, Y0) != _keyColor)
		{
			_outFill.x = (float)X;
			_outFill.y = (float)Y0;
			return true;
		}
		if (_maskBitmap[Y1][X] == false && GetPixel(_hdc, X, Y1) != _keyColor)
		{
			_outFill.x = (float)X;
			_outFill.y = (float)Y1;
			return true;
		}
	}

	for (int Y = Y0; Y < Y1; ++Y)
	{
		if (_maskBitmap[Y][X1] == false && GetPixel(_hdc, X1, Y) != _keyColor)
		{
			_outFill.x = (float)X0;
			_outFill.y = (float)Y;
			return true;
		}
		if (_maskBitmap[Y][X1] == false && GetPixel(_hdc, X1, Y) != _keyColor)
		{
			_outFill.x = (float)X1;
			_outFill.y = (float)Y;
			return true;
		}
	}
	return false;
}

void Sprite::GetTightBounds(HDC _hdc, std::vector<std::vector<bool>> _maskBitmap, COLORREF& _keyColor,
	CD2DPointF& _outOrigin, CD2DPointF& _outDimension)
{
	_outOrigin.x = 0;
	_outOrigin.y = 0;
	_outDimension.x = (float)_maskBitmap[0].size();
	_outDimension.y = (float)_maskBitmap.size();


	// TightenBounds
	int top = (int)_outOrigin.y;
	int bottom = (int)_outOrigin.y + (int)_outDimension.y - 1;
	int left = (int)_outOrigin.x;
	int right = (int)_outOrigin.x + (int)_outDimension.x - 1;

	while (top < bottom && IsRowEmpty(_hdc, _keyColor, left, right, top))
	{
		++top;
	}
	while (bottom >= top && IsRowEmpty(_hdc, _keyColor, left, right, bottom))
	{
		--bottom;
	}
	while (left < right && IsColumnEmpty(_hdc, _keyColor, left, top, bottom))
	{
		++left;
	}
	while (right >= left && IsColumnEmpty(_hdc, _keyColor, right, top, bottom))
	{
		--right;
	}
	_outOrigin.x = (float)left;
	_outOrigin.y = (float)top;
	_outDimension.x = (float)right - left + 1;
	_outDimension.y = (float)bottom - top + 1;
}

bool Sprite::IsRowEmpty(HDC _hdc, COLORREF& _keyColor, int _X0, int _X1, int _Y)
{
	return IsRowEqual(_hdc, _keyColor, _X0, _X1, _Y);
}

bool Sprite::IsRowEqual(HDC _hdc, COLORREF& _keyColor, int _X0, int _X1, int _Y)
{
	for (int X = _X0; X <= _X1; ++X)
	{
		if (GetPixel(_hdc, X, _Y) != _keyColor)
		{
			return false;
		}
	}
	return true;
}

bool Sprite::IsColumnEmpty(HDC _hdc, COLORREF& _keyColor, int _X, int _Y0, int _Y1)
{
	return IsColumnEqual(_hdc, _keyColor, _X, _Y0, _Y1);
}

bool Sprite::IsColumnEqual(HDC _hdc, COLORREF& _keyColor, int _X, int _Y0, int _Y1)
{
	for (int Y = _Y0; Y <= _Y1; ++Y)
	{
		if (GetPixel(_hdc, _X, Y) != _keyColor)
		{
			return false;
		}
	}
	return true;
}

void Sprite::FillRect(std::vector<std::vector<bool>>& _maskBitmap, int _startX, int _startY, int _inWidth,
	int _inHeight)
{
	const int X0 = _startX;
	const int Y0 = _startY;
	const int X1 = _startX + _inWidth - 1;
	const int Y1 = _startY + _inHeight - 1;
	for (int Y = Y0; Y <= Y1; ++Y)
	{
		for (int X = X0; X <= X1; ++X)
		{
			_maskBitmap[Y][X] = true;
		}
	}
}
