#pragma once

#include <afx.h>
#include <string>

class ExtractedSprite : public CObject
{
public:
	ExtractedSprite();
	ExtractedSprite(float _left, float _top, float _right, float _bottom, float _pivotX, float _pivotY);
	virtual ~ExtractedSprite();

	void Render(CRenderTarget* _pRenderTarget);

	std::wstring name{};
	float left = 0.f, top = 0.f, right = 0.f, bottom = 0.f;

	// 피봇의 기준은 0 ~ 1 사이의 비율로 결정
	float pivotX = 0.f, pivotY = 0.f;

	bool isSelected = false;
};

