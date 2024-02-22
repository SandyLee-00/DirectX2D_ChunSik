///Animation 클래스
///by.김예리나
/// 애니메이션컴포넌트
#pragma once

#include "Component.h"
#include "DrawObj.h"
class GraphicsEngine;
class Animator;

class Animation : public Component
{
	DrawObj* spriteObj;
	Animator* ani;
	Object* owner;
	std::wstring txtPath;
	std::wstring imagePath;
	std::string name;
	int nowMotion;
	int nowSprite;
	int thisSprite;
	bool isPlay;
	float frameAnimation;
	float getFrame;
	int posX;
	int posY;
	int gotNum;
	Vector2	offset;

public:
	Animation(Object* owner);
	virtual ~Animation();

	void Update(float _dt = 0) override;
	void LateUpdate() override {};
	void Render(GraphicsEngine* _graphicsEngine) override;
	void DebugRender(GraphicsEngine* _graphicsEngine) override {};

	void SetSpriteRes(int _getIndex, std::wstring _txtPath, std::string _name,int _x, int _y);
	void Play();
	void Stop(int _index);
	void Init();
	Vector2 GetOffset() const { return offset; }
	void SetOffset(Vector2 val) { offset = val; }
};

