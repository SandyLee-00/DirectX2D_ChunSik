#include "pch.h"
#include "ExtractedSprite.h"

#include <algorithm>

ExtractedSprite::ExtractedSprite()
{

}

ExtractedSprite::ExtractedSprite(float _left, float _top, float _right, float _bottom, float _pivotX, 
	float _pivotY) : left(_left), top(_top), right(_right), bottom(_bottom), pivotX(_pivotX), pivotY(_pivotY)
{

}

ExtractedSprite::~ExtractedSprite()
{

}

void ExtractedSprite::Render(CRenderTarget* _pRenderTarget)
{
	D2D1::ColorF color = D2D1::ColorF::Green;
	if (this->isSelected)
	{
		color = D2D1::ColorF::Red;
	}
	else
	{
		color = D2D1::ColorF::Green;
	}

	CD2DSolidColorBrush* pTempBrush1 = new CD2DSolidColorBrush(_pRenderTarget, D2D1::ColorF(color));
	CD2DSolidColorBrush* pTempBrush2 = new CD2DSolidColorBrush(_pRenderTarget, 
		D2D1::ColorF(D2D1::ColorF::Blue));

	// 상자 Render
	_pRenderTarget->DrawRectangle(CD2DRectF(this->left, this->top, this->right, this->bottom), pTempBrush1);

	// pivot render

	// 왼쪽에서 아래로의 방향이 아니라 다른 방향으로 드래그했을 때
	if (this->left > this->right)
	{
		std::swap(this->left, this->right);
	}
	if (this->top > this->bottom)
	{
		std::swap(this->top, this->bottom);
	}
	float pivotPosX = this->left + abs(this->right - this->left) * this->pivotX;
	float pivotPosY = this->top + abs(this->bottom - this->top) * this->pivotY;

	_pRenderTarget->DrawRectangle(CD2DRectF(pivotPosX - 2, pivotPosY - 2, pivotPosX + 2, pivotPosY + 2), 
		pTempBrush2);

	pTempBrush1->Destroy();
	pTempBrush1 = nullptr;
	pTempBrush2->Destroy();
	pTempBrush2 = nullptr;
}
